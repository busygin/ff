/*
 * fast_compiler.cpp
 *
 *  Created on: Jul 6, 2014
 *      Author: busygin
 */


#include <cstdlib>
#include <ctime>

#include <string>
#include <vector>
#include <map>
#include <set>

#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/optional.hpp>


using namespace boost::property_tree;


enum class FieldOperator : size_t {
	NO_OPERATOR,
	CONSTANT,
	COPY,
	DEFAULT,
	DELTA,
	INCREMENT
};

std::vector<std::string> field_operator_cpp_types = {
	"NoOperator",
	"Constant",
	"Copy",
	"Default",
	"Delta",
	"Increment"
};

std::map<std::string,std::string> fast_field_cpp_types = {
	{"string", "std::string"},
	{"int32", "int32_t"},
	{"uInt32", "uint32_t"},
	{"int64", "int64_t"},
	{"uInt64", "uint64_t"},
	{"length", "uint64_t"},
	{"decimal", "Decimal"}
};

const char req_suffix[2][10] = {"Optional", "Mandatory"};

struct FieldInTemplate {
	int number;
	std::string name;
	FieldOperator op;
	boost::optional<FieldOperator> op2; // used for exponent in case of decimal
	std::string cpp_type;
	boost::optional<std::string> value;
	boost::optional<std::string> value2; // used for exponent in case of decimal
	bool is_required;
	bool is_length_of_seq;
	uint8_t bits_in_pmap;
	FieldInTemplate() : is_length_of_seq(false), bits_in_pmap(0) { }
};

struct FastSeqSpec {
	size_t pos;
	FieldInTemplate noxxx_field;
	std::string name;
	std::vector<FieldInTemplate> fields;
	std::vector<FastSeqSpec> seqs;
	size_t bits_in_pmap;
	FastSeqSpec() : bits_in_pmap(0) { }
};

struct FastMsgSpec {
	int number;
	std::string name;
	std::string callback_type;
	std::vector<FieldInTemplate> fields;
	std::vector<FastSeqSpec> seqs;
	char msgtype;
	size_t bits_in_pmap;
	bool has_md_entries;
	FastMsgSpec() : bits_in_pmap(0), has_md_entries(false) { }
};

std::set<std::string> msg_callback_types;

void load_field_in_template_spec(const std::string& cpp_type, const ptree& f_attr, FieldInTemplate& f) {
	f.op = FieldOperator::NO_OPERATOR;
	f.cpp_type = cpp_type;
	for(const auto &pf : f_attr) {
		const ptree& f_attr = pf.second;
		if (pf.first=="<xmlattr>") {
			f.number = f_attr.get<int>("id");
			f.name = f_attr.get<std::string>("name");
			boost::optional<std::string> pres = f_attr.get_optional<std::string>("presence");
			f.is_required = (!pres || pres.get()!="optional");
		} else if (pf.first=="constant") {
			f.op = FieldOperator::CONSTANT;
			f.value = f_attr.get_child("<xmlattr>").get_optional<std::string>("value");
		} else if (pf.first=="copy")
			f.op = FieldOperator::COPY;
		else if (pf.first=="default") {
			f.op = FieldOperator::DEFAULT;
			boost::optional<const ptree&> o_attr = f_attr.get_child_optional("<xmlattr>");
			if (o_attr)
				f.value = o_attr->get_optional<std::string>("value");
		} else if (pf.first=="delta")
			f.op = FieldOperator::DELTA;
		else if (pf.first=="increment")
			f.op = FieldOperator::INCREMENT;
	}
	if (f.op==FieldOperator::COPY || f.op==FieldOperator::DEFAULT || f.op==FieldOperator::INCREMENT || (f.op==FieldOperator::CONSTANT && !f.is_required))
		++f.bits_in_pmap;
}

void load_decimal_field_in_template_spec(const ptree& f_attr, FieldInTemplate& f) {
	f.op = FieldOperator::NO_OPERATOR;
	f.cpp_type = "Decimal";
	const ptree& d_attr = f_attr.get_child("<xmlattr>");
	f.number = d_attr.get<int>("id");
	f.name = d_attr.get<std::string>("name");
	boost::optional<std::string> pres = d_attr.get_optional<std::string>("presence");
	f.is_required = (!pres || pres.get()!="optional");
	const ptree& m_attr = f_attr.get_child("mantissa");
	for(const auto &pm : m_attr) {
		const ptree& m_attr = pm.second;
		if (pm.first=="constant") {
			f.op = FieldOperator::CONSTANT;
			f.value = m_attr.get_child("<xmlattr>").get_optional<std::string>("value");
		} else if (pm.first=="copy")
			f.op = FieldOperator::COPY;
		else if (pm.first=="default") {
			f.op = FieldOperator::DEFAULT;
			boost::optional<const ptree&> o_attr = m_attr.get_child_optional("<xmlattr>");
			if (o_attr)
				f.value = o_attr->get_optional<std::string>("value");
		} else if (pm.first=="delta")
			f.op = FieldOperator::DELTA;
		else if (pm.first=="increment")
			f.op = FieldOperator::INCREMENT;
	}
	if (f.op==FieldOperator::COPY || f.op==FieldOperator::DEFAULT || f.op==FieldOperator::INCREMENT || (f.op==FieldOperator::CONSTANT && !f.is_required))
		++f.bits_in_pmap;

	f.op2 = FieldOperator::NO_OPERATOR;
	const ptree& e_attr = f_attr.get_child("exponent");
	for(const auto &pe : e_attr) {
		const ptree& e_attr = pe.second;
		if (pe.first=="constant") {
			f.op2 = FieldOperator::CONSTANT;
			f.value2 = e_attr.get_child("<xmlattr>").get_optional<std::string>("value");
		} else if (pe.first=="copy")
			f.op2 = FieldOperator::COPY;
		else if (pe.first=="default") {
			f.op2 = FieldOperator::DEFAULT;
			boost::optional<const ptree&> o_attr = e_attr.get_child_optional("<xmlattr>");
			if (o_attr)
				f.value2 = o_attr->get_optional<std::string>("value");
		} else if (pe.first=="delta")
			f.op2 = FieldOperator::DELTA;
		else if (pe.first=="increment")
			f.op2 = FieldOperator::INCREMENT;
	}
	if (*f.op2==FieldOperator::COPY || *f.op2==FieldOperator::DEFAULT || *f.op2==FieldOperator::INCREMENT || (*f.op2==FieldOperator::CONSTANT && !f.is_required))
		++f.bits_in_pmap;
}

void load_seq_spec(const ptree& s_spec, FastSeqSpec& s) {
	size_t pos=0;
	for(const auto &pr : s_spec) {
		const ptree& s_attr = pr.second;
		if (pr.first=="<xmlattr>")
			s.name = s_attr.get<std::string>("name");
		else if (pr.first=="length")
			load_field_in_template_spec(fast_field_cpp_types[pr.first], s_attr, s.noxxx_field);
		else if (pr.first=="sequence") {
			FastSeqSpec &s2 = *(s.seqs.insert(s.seqs.end(), FastSeqSpec()));
			load_seq_spec(s_attr, s2);
			s.fields.push_back(s2.noxxx_field);
			s.fields.back().is_length_of_seq = true;
			s2.pos = ++pos;
		} else if (pr.first=="decimal") {
			FieldInTemplate& f = *(s.fields.insert(s.fields.end(), FieldInTemplate()));
			load_decimal_field_in_template_spec(s_attr, f);
			s.bits_in_pmap += f.bits_in_pmap;
			++pos;
		} else if (pr.first!="<xmlcomment>") {
			FieldInTemplate& f = *(s.fields.insert(s.fields.end(), FieldInTemplate()));
			load_field_in_template_spec(fast_field_cpp_types[pr.first], s_attr, f);
			s.bits_in_pmap += f.bits_in_pmap;
			++pos;
		}
	}
}

void load_msg_specs(const ptree& templates, std::vector<FastMsgSpec>& msgs) {
	for(const auto &pt : templates) if(pt.first=="template") {
		const ptree& s_fields = pt.second;
		FastMsgSpec& m = *(msgs.insert(msgs.end(), FastMsgSpec()));
		size_t pos=0;
		for(const auto &ps : s_fields) {
			const ptree& m_attr = ps.second;
			if (ps.first=="<xmlattr>") {
				m.number = m_attr.get<int>("id");
				m.name = m_attr.get<std::string>("name");
				std::string::iterator p(m.name.begin());
				while (p!=m.name.end() && *p!='_') ++p;
				m.callback_type.assign(m.name.begin(), p);
				msg_callback_types.insert(m.callback_type);
			} else if (ps.first=="sequence") {
				FastSeqSpec& s = *(m.seqs.insert(m.seqs.end(), FastSeqSpec()));
				load_seq_spec(m_attr, s);
				if (s.name=="MDEntries")
					m.has_md_entries = true;
				m.fields.push_back(s.noxxx_field);
				m.fields.back().is_length_of_seq = true;
				s.pos = ++pos;
			} else if (ps.first=="decimal") {
				FieldInTemplate& f = *(m.fields.insert(m.fields.end(), FieldInTemplate()));
				load_decimal_field_in_template_spec(m_attr, f);
				m.bits_in_pmap += f.bits_in_pmap;
				++pos;
			} else if (ps.first!="<xmlcomment>") {
				FieldInTemplate& f = *(m.fields.insert(m.fields.end(), FieldInTemplate()));
				load_field_in_template_spec(fast_field_cpp_types[ps.first], m_attr, f);
				m.bits_in_pmap += f.bits_in_pmap;
				++pos;
			} else {
				const std::string& comment = m_attr.get_value<std::string>();
				size_t spos = comment.find("DEPRECATED");
				if (spos != std::string::npos) {
					msgs.pop_back();
					break;
				}
			}
		}
	}
}

template<typename Container, typename FieldPrinter, typename SeqPrinter>
void print_field_container(std::ostream& os, const Container& c, FieldPrinter fprn, SeqPrinter sprn) {
	std::vector<FastSeqSpec>::const_iterator cs(c.seqs.begin());
	size_t s_pos = (cs==c.seqs.end() ? static_cast<size_t>(-1) : cs->pos);
	size_t pos;
	for(pos=0; pos<c.fields.size(); ++pos) {
		while(pos==s_pos) {
			sprn(os, *cs);
			++cs;
			s_pos = (cs==c.seqs.end() ? static_cast<size_t>(-1) : cs->pos);
		}
		fprn(os, c.fields[pos]);
	}
	while(pos==s_pos) {
		sprn(os, *cs);
		++cs;
		s_pos = (cs==c.seqs.end() ? static_cast<size_t>(-1) : cs->pos);
	}
}

void print_field_operator(std::ostream &os, const FieldInTemplate& f) {
	if (f.op2) { // this is Decimal
		if (f.value) {
			os << "\tclass " << f.name << "MantOp : public " << field_operator_cpp_types[static_cast<size_t>(f.op)] << req_suffix[f.is_required] << "Field<int64_t," << f.number << "> {\n";
			os << "\tpublic:\n";
			os << "\t\t" << f.name << "MantOp() : " << field_operator_cpp_types[static_cast<size_t>(f.op)] << req_suffix[f.is_required] << "Field<int64_t," << f.number << ">(" << *f.value << ") { }\n";
			os << "\t};\n";
		} else
			os << "\tusing " << f.name << "MantOp = " << field_operator_cpp_types[static_cast<size_t>(f.op)] << req_suffix[f.is_required] << "Field<int64_t," << f.number << ">;\n";
		os << '\t' << f.name << "MantOp op_" << f.name << "Mant;\n";
		if (f.value2) {
			os << "\tclass " << f.name << "ExpOp : public " << field_operator_cpp_types[static_cast<size_t>(*f.op2)] << req_suffix[f.is_required] << "Field<int32_t," << f.number << "> {\n";
			os << "\tpublic:\n";
			os << "\t\t" << f.name << "ExpOp() : " << field_operator_cpp_types[static_cast<size_t>(*f.op2)] << req_suffix[f.is_required] << "Field<int32_t," << f.number << ">(" << *f.value << ") { }\n";
			os << "\t};\n";
		} else
			os << "\tusing " << f.name << "ExpOp = " << field_operator_cpp_types[static_cast<size_t>(*f.op2)] << req_suffix[f.is_required] << "Field<int32_t," << f.number << ">;\n";
		os << '\t' << f.name << "ExpOp op_" << f.name << "Exp;\n\n";
	} else {
		if (f.value) {
			os << "\tclass " << f.name << "Op : public " << field_operator_cpp_types[static_cast<size_t>(f.op)] << req_suffix[f.is_required] << "Field<" << f.cpp_type << ',' << f.number << "> {\n";
			os << "\tpublic:\n";
			char quot = (f.cpp_type=="std::string" ? '\"' : 0);
			os << "\t\t" << f.name << "Op() : " << field_operator_cpp_types[static_cast<size_t>(f.op)] << req_suffix[f.is_required] << "Field<" << f.cpp_type << ',' << f.number << ">(";
			if (quot) os << quot;
			os << *f.value;
			if (quot) os << quot;
			os << ") { }\n";
			os << "\t};\n";
		} else
			os << "\tusing " << f.name << "Op = " << field_operator_cpp_types[static_cast<size_t>(f.op)] << req_suffix[f.is_required] << "Field<" << f.cpp_type << ',' << f.number << ">;\n";
		os << '\t' << f.name << "Op op_" << f.name << ";\n\n";
	}
}

void print_field_operator_sequence(std::ostream &os, const FastSeqSpec& s) {
	print_field_container(os, s, print_field_operator, print_field_operator_sequence);
}

void print_reset(std::ostream &os, const FieldInTemplate& f) {
	if (f.op2) {
		os << "\t\top_" << f.name << "Mant.reset();\n";
		os << "\t\top_" << f.name << "Exp.reset();\n";
	} else
		os << "\t\top_" << f.name << ".reset();\n";
}

void print_reset_sequence(std::ostream &os, const FastSeqSpec& s) {
	print_field_container(os, s, print_reset, print_reset_sequence);
}

void print_ops(std::ostream &os, const std::vector<FastMsgSpec>& msgs) {
	for(const auto &m : msgs) {
		os << "//----------------------------------\n\n";

		os << "struct " << m.name << "FieldOp {\n";

		print_field_container(os, m, print_field_operator, print_field_operator_sequence);

		os << "\tstatic constexpr uint32_t number() { return " << m.number << "; }\n\n";

		os << "\tvoid reset() {\n";
		print_field_container(os, m, print_reset, print_reset_sequence);
		os << "\t}\n";

		os << "}; // " << m.name << "FieldOp\n\n";
	}
}


void print_seqs(std::ostream &os, const std::vector<FastSeqSpec>& seqs, const std::string& m_name, const std::string& indent) {
	for(const auto &s : seqs) {
		os << indent << "struct " << s.name << " {\n";
		print_seqs(os, s.seqs, m_name, indent+"\t");

		print_field_container (
			os, s,
			[&indent](std::ostream& os, const FieldInTemplate& f) {
				os << indent << "\tusing " << f.name << " = FastField<" << f.cpp_type << ',' << f.number << ">;\n";
				os << indent << '\t' << f.name << " f_" << f.name << ";\n\n";
			},
			[&indent](std::ostream& os, const FastSeqSpec& s) {
				os << indent << "\tstd::vector<" << s.name << "> s_" << s.name << ";\n\n";
			}
		);

		print_field_container (
			os, s,
			[&indent](std::ostream& os, const FieldInTemplate& f) {
				if (!f.is_length_of_seq) {
					os << indent << "\tvoid set_" << f.name << "(const " << f.cpp_type << "& v) {\n";
					os << indent << "\t\tf_" << f.name << ".assign(v);\n";
					os << indent << "\t}\n";
				}
			},
			[&indent](std::ostream& os, const FastSeqSpec& s) {
				os << indent << "\tvoid append_" << s.name << "(const " << s.name << "& v) {\n";
				os << indent << "\t\ts_" << s.name << ".push_back(v);\n";
				os << indent << "\t\tf_" << s.noxxx_field.name << ".assign(s_" << s.name << ".size());\n";
				os << indent << "\t}\n";
			}
		);

		os << indent << "\tvoid scan(const char* &buf, const char* end, " << m_name << "FieldOp& op_" << m_name << ", PMap& pm) {\n";
		print_field_container (
			os, s,
			[&m_name,&indent](std::ostream& os, const FieldInTemplate& f) {
				if (f.op2)  // Decimal
					os << indent << "\t\tf_" << f.name << ".scan(buf, end, op_" << m_name << ".op_" << f.name << "Mant, op_" << m_name << ".op_" << f.name << "Exp, pm);\n";
				else
					os << indent << "\t\tf_" << f.name << ".scan(buf, end, op_" << m_name << ".op_" << f.name << ", pm);\n";
			},
			[&m_name,&indent](std::ostream& os, const FastSeqSpec& s) {
				os << indent << "\t\tif (!f_" << s.noxxx_field.name << ".defined()) throw UnknownLength(\"" << s.name << "\");\n";
				os << indent << "\t\tuint64_t n_" << s.name << "_elems = f_" << s.noxxx_field.name << ".value();\n";
				os << indent << "\t\ts_" << s.name << ".resize(n_" << s.name << "_elems);\n";
				os << indent << "\t\tfor(auto &s : s_" << s.name << ") {\n";
				os << indent << "\t\t\tfast_scan_without_null(pmap_, buf, end);\n";
				os << indent << "\t\t\ts.scan(buf, end, op_" << m_name << ", pmap_);\n";
				os << indent << "\t\t}\n";
			}
		);
		os << indent << "\t} // " << s.name << "::scan()\n";

		os << indent << "\tvoid encode(char* &buf, char* end, " << m_name << "FieldOp& op_" << m_name << ", PMap& pmap) {\n";
		print_field_container (
			os, s,
			[&m_name,&indent](std::ostream& os, const FieldInTemplate& f) {
				if (f.op2)  // Decimal
					os << indent << "\t\tf_" << f.name << ".encode(buf, end, op_" << m_name << ".op_" << f.name << "Mant, op_" << m_name << ".op_" << f.name << "Exp, pmap);\n";
				else
					os << indent << "\t\tf_" << f.name << ".encode(buf, end, op_" << m_name << ".op_" << f.name << ", pmap);\n";
			},
			[&m_name,&indent](std::ostream& os, const FastSeqSpec& s) {
				size_t pmap_len = (s.bits_in_pmap==0 ? 1 : (s.bits_in_pmap+6)/7);
				os << indent << "\t\tfor(auto &s : s_" << s.name << ") {\n";
				os << indent << "\t\t\tchar* s_buf(buf);\n";
				os << indent << "\t\t\tbuf += " << pmap_len << ";\n";
				os << "#ifdef BUFFER_RANGE_CHECK\n";
				os << indent << "\t\t\tif (buf>end)\n";
				os << indent << "\t\t\t\tthrow UnexpectedEndOfMessageBuffer();\n";
				os << "#endif\n";
				os << indent << "\t\t\tpmap_.clear();\n";
				os << indent << "\t\t\ts.encode(buf, end, op_" << m_name << ", pmap_);\n";
				os << indent << "\t\t\tfast_encode_without_null(pmap_, s_buf, s_buf+" << pmap_len << ");\n";
				os << indent << "\t\t}\n";
			}
		);
		os << indent << "\t} // " << s.name << "::encode()\n";

		if (!s.seqs.empty()) {
			os << indent << "private:\n";
			os << indent << "\tPMap pmap_;\n";
		}

		os << indent << "}; // " << s.name << '\n';
	}
}

void print_msgs(std::ostream &os, const std::vector<FastMsgSpec>& msgs) {
	for(const auto &m : msgs) {
		os << "//----------------------------------\n\n";

		os << "struct " << m.name << " {\n";

		print_seqs(os, m.seqs, m.name, "\t");

		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInTemplate& f) {
				os << "\tusing " << f.name << " = FastField<" << f.cpp_type << ',' << f.number << ">;\n";
				os << '\t' << f.name << " f_" << f.name << ";\n\n";
			},
			[](std::ostream& os, const FastSeqSpec& s) {
				os << "\tstd::vector<" << s.name << "> s_" << s.name << ";\n\n";
			}
		);

		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInTemplate& f) {
				if (!f.is_length_of_seq) {
					os << "\tvoid set_" << f.name << "(const " << f.cpp_type << "& v) {\n";
					os << "\t\tf_" << f.name << ".assign(v);\n";
					os << "\t}\n";
				}
			},
			[](std::ostream& os, const FastSeqSpec& s) {
				os << "\tvoid append_" << s.name << "(const " << s.name << "& v) {\n";
				os << "\t\ts_" << s.name << ".push_back(v);\n";
				os << "\t\tf_" << s.noxxx_field.name << ".assign(s_" << s.name << ".size());\n";
				os << "\t}\n";
			}
		);

		os << "\n\tvoid clear() {\n";
		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInTemplate& f){os << "\t\tf_" << f.name << ".clear();\n";},
			[](std::ostream& os, const FastSeqSpec& s){os << "\t\tf_" << s.noxxx_field.name << ".clear();\n";}
		);
		os << "\t} // " << m.name << "::clear()\n\n";

		if (m.has_md_entries)
			os << "\ttemplate<typename Callback>\n";
		os << "\tvoid scan(const char* &buf, const char* end, " << m.name << "FieldOp& op_" << m.name << ", PMap& pm";
		if (m.has_md_entries)
			os << ", Callback on_first_MDEntry";
		os << ") {\n";
		print_field_container (
			os, m,
			[&m](std::ostream& os, const FieldInTemplate& f) {
				if (f.op2) {  // Decimal
					/*os << "\t\top_" << m.name << ".op_" << f.name << "Mant.scan(buf, end, pm);\n";
					os << "\t\top_" << m.name << ".op_" << f.name << "Exp.scan(buf, end, pm);\n";
					os << "\t\thas_" << f.name << " = (op_" << m.name << ".op_" << f.name << "Mant.value() && op_" << m.name << ".op_" << f.name << "Exp.value());\n";
					os << "\t\tif (has_" << f.name << ") {\n";
					os << "\t\t\tf_" << f.name << ".value().mantissa = *op_" << m.name << ".op_" << f.name << "Mant.value();\n";
					os << "\t\t\tf_" << f.name << ".value().exponent = *op_" << m.name << ".op_" << f.name << "Exp.value();\n";
					os << "\t\t}\n";*/
					os << "\t\tf_" << f.name << ".scan(buf, end, op_" << m.name << ".op_" << f.name << "Mant, op_" << m.name << ".op_" << f.name << "Exp, pm);\n";
				} else
					os << "\t\tf_" << f.name << ".scan(buf, end, op_" << m.name << ".op_" << f.name << ", pm);\n";
			},
			[&m](std::ostream& os, const FastSeqSpec& s) {
				os << "\t\tif (!f_" << s.noxxx_field.name << ".defined()) throw UnknownLength(\"" << s.name << "\");\n";
				os << "\t\tuint64_t n_" << s.name << "_elems = f_" << s.noxxx_field.name << ".value();\n";
				os << "\t\ts_" << s.name << ".resize(n_" << s.name << "_elems);\n";
				if (s.name=="MDEntries") {
					os << "\t\tfast_scan_without_null(pmap_, buf, end);\n";
					os << "\t\ts_" << s.name << "[0].scan(buf, end, op_" << m.name << ", pmap_);\n";
					os << "\t\tif (on_first_MDEntry())\n";
					os << "\t\t\treturn;\n";
					os << "\t\tfor(std::vector<" << s.name << ">::iterator ps(s_" << s.name << ".begin()+1); ps!=s_" << s.name << ".end(); ++ps) {\n";
					os << "\t\t\tfast_scan_without_null(pmap_, buf, end);\n";
					os << "\t\t\tps->scan(buf, end, op_" << m.name << ", pmap_);\n";
					os << "\t\t}\n";
				} else {
					os << "\t\tfor(auto &s : s_" << s.name << ") {\n";
					os << "\t\t\tfast_scan_without_null(pmap_, buf, end);\n";
					os << "\t\t\ts.scan(buf, end, op_" << m.name << ", pmap_);\n";
					os << "\t\t}\n";
				}
			}
		);
		os << "\t} // " << m.name << "::scan()\n\n";

		os << "\tvoid encode(char* &buf, char* end, " << m.name << "FieldOp& op_" << m.name << ", PMap& pmap) {\n";
		print_field_container (
			os, m,
			[&m](std::ostream& os, const FieldInTemplate& f) {
				if (f.op2) {  // Decimal
					/*os << "\t\tif (has_" << f.name << ") {\n";
					os << "\t\t\top_" << m.name << ".op_" << f.name << "Mant.value() = f_" << f.name << ".value().mantissa;\n";
					os << "\t\t\top_" << m.name << ".op_" << f.name << "Exp.value() = f_" << f.name << ".value().exponent;\n";
					os << "\t\t} else {\n";
					os << "\t\t\top_" << m.name << ".op_" << f.name << "Mant.value().disable();\n";
					os << "\t\t\top_" << m.name << ".op_" << f.name << "Exp.value().disable();\n";
					os << "\t\t}\n";
					os << "\t\top_" << m.name << ".op_" << f.name << "Mant.encode(buf, end, pmap);\n";
					os << "\t\top_" << m.name << ".op_" << f.name << "Exp.encode(buf, end, pmap);\n";*/
					os << "\t\tf_" << f.name << ".encode(buf, end, op_" << m.name << ".op_" << f.name << "Mant, op_" << m.name << ".op_" << f.name << "Exp, pmap);\n";
				} else
					os << "\t\tf_" << f.name << ".encode(buf, end, op_" << m.name << ".op_" << f.name << ", pmap);\n";
			},
			[&m](std::ostream& os, const FastSeqSpec& s) {
				size_t pmap_len = (s.bits_in_pmap==0 ? 1 : (s.bits_in_pmap+6)/7);
				os << "\t\tfor(auto &s : s_" << s.name << ") {\n";
				os << "\t\t\tchar* s_buf(buf);\n";
				os << "\t\t\tbuf += " << pmap_len << ";\n";
				os << "#ifdef BUFFER_RANGE_CHECK\n";
				os << "\t\t\tif (buf>end)\n";
				os << "\t\t\t\tthrow UnexpectedEndOfMessageBuffer();\n";
				os << "#endif\n";
				os << "\t\t\tpmap_.clear();\n";
				os << "\t\t\ts.encode(buf, end, op_" << m.name << ", pmap_);\n";
				os << "\t\t\tfast_encode_without_null(pmap_, s_buf, s_buf+" << pmap_len << ");\n";
				os << "\t\t}\n";
			}
		);
		os << "\t} // " << m.name << "::encode()\n";

		os << "\n\tstatic constexpr uint32_t number() { return " << m.number << "; }\n";

		if (!m.seqs.empty()) {
			os << "\nprivate:\n";
			os << "\tPMap pmap_;\n";
		}

		os << "}; // " << m.name << "\n\n";
	}
}

void print_parser(std::ostream &os, const std::vector<FastMsgSpec>& msgs) {
	os << "template<typename Handler>\n";
	os << "class FastParser {\n";
	os << "public:\n";
	os << "\tFastParser(Handler& handler) : handler_(handler), template_id_(0) { }\n";

	for(const auto &m : msgs)
		os << '\t' << m.name << " m_" << m.name << "_;\n";
	for(const auto &m : msgs)
		os << '\t' << m.name << "FieldOp op_" << m.name << "_;\n";

	os << "\tvoid reset() {\n";
	for(const auto &m : msgs)
		os << "\t\top_" << m.name << "_.reset();\n";
	os << "\t\ttemplate_id_ = 0;\n";
	os << "\t}\n";

	os << "\tvoid scan(const char* &buf, const char* end) {\n";
	os << "\t\tfast_scan_without_null(pmap_, buf, end);\n";
	os << "\t\tif (pmap_.fetch_bit())\n";
	os << "\t\t\tfast_scan_without_null(template_id_, buf, end);\n";
	os << "\t\telse\n";
	os << "\t\t\tif (!template_id_) throw MissingFastTemplateID();\n";
	os << "\t\tswitch(template_id_) {\n";
	for(const auto &m : msgs) {
		os << "\t\tcase " << m.name << "::number():\n";
		os << "\t\t\tm_" << m.name << "_.scan(buf, end, op_" << m.name << "_, pmap_";
		if (m.has_md_entries)
			os << ", OnFirstMDEntryFunctor<Handler, " << m.name << ">(handler_, m_" << m.name << "_)";
		os << ");\n";
		os << "\t\t\thandler_.on_" << m.callback_type << "(m_" << m.name << "_);\n";
		os << "\t\t\tbreak;\n";
	}
	os << "\t\t}\n";
	os << "\t}\n";

	for(const auto &m : msgs) {
		size_t pmap_len = m.bits_in_pmap/7 + 1;
		os << "\tvoid encode_" << m.name << "(char* &buf, char* end) {\n";
		os << "\t\tchar* s_buf(buf);\n";
		os << "\t\tbuf += " << pmap_len << ";\n";
		os << "#ifdef BUFFER_RANGE_CHECK\n";
		os << "\t\tif (buf>end)\n";
		os << "\t\t\tthrow UnexpectedEndOfMessageBuffer();\n";
		os << "#endif\n";
		os << "\t\tpmap_.clear();\n";
		os << "\t\tpmap_.push_back(true);\n";
		os << "\t\tfast_encode_without_null<uint32_t>(" << m.name << "::number(), buf, end);\n";
		os << "\t\tm_" << m.name << "_.encode(buf, end, op_" << m.name << "_, pmap_);\n";
		os << "\t\tfast_encode_without_null(pmap_, s_buf, s_buf+" << pmap_len << ");\n";
		os << "\t}\n";
	}

	os << "private:\n";
	os << "\tHandler& handler_;\n";
	os << "\tuint32_t template_id_;\n";
	os << "\tPMap pmap_;\n";
	os << "}; // FastParser\n\n";
}

void print_base_handler(std::ostream &os, const std::vector<FastMsgSpec>& msgs) {
	os << "class BaseFastHandler {\n";
	os << "public:\n";
	for(const auto &c : msg_callback_types) {
		os << "\ttemplate<typename Msg> void on_" << c << "(const Msg& m) { }\n";
	}
	for(const auto &m : msgs) {
		if (m.has_md_entries)
			os << "\tbool on_first_MDEntry(const " << m.name << "& m) { return false; }\n";
	}
	os << "}; // BaseFastHandler\n";
}


void fast_xml_compiler(std::ostream &os, const std::string& xml_file) {
	ptree xml_spec;
	read_xml(xml_file, xml_spec);

	const ptree& templates = xml_spec.get_child("templates");

	std::vector<FastMsgSpec> msgs;
	load_msg_specs(templates, msgs);

	os << "// Code generated from " << xml_file << "\n\n";
	os << "#ifndef FAST_COMPILED_H_\n";
	os << "#define FAST_COMPILED_H_\n\n";
	os << "#include <cstdint>\n";
	os << "#include <string>\n";
	os << "#include <vector>\n";
	os << "#include \"message.h\"\n";
	os << "#include \"fast_fields.h\"\n";
	os << "#include \"pmap.h\"\n";
	os << "#include \"utils.h\"\n\n";
	os << "namespace FIX {\n\n";

	print_ops(os, msgs);
	print_msgs(os, msgs);

	print_parser(os, msgs);
	print_base_handler(os, msgs);

	os << "\n}\n\n";
	os << "\n#endif\t// FAST_COMPILED_H_\n";
}


int main(int argc, char** argv) {
	if (argc==3) {
		std::ofstream os(argv[2]);
		fast_xml_compiler(os, argv[1]);
		os.close();
	} else
		std::cout << "Usage: fast_compiler <xml_template_file> <cpp_header_output_file>\n";
	return 0;
}
