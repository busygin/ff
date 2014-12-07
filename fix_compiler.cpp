/*
 * fix_compiler.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: busygin
 */


#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include <exception>
#include <ostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <cstdint>
#include <cstdlib>

using namespace boost::property_tree;

class InvalidFieldTypeException: public std::exception {
public:
	InvalidFieldTypeException(const std::string& s) : type_name(s) { }

private:
	const std::string& type_name;

	virtual const char* what() const throw() {
		return type_name.c_str();
	}
};

enum class FixMsgCat : size_t { ADMIN, APP };

#define FIXNFIELDTYPES 21

enum class FixFieldType : size_t {
    AMT,
    BOOLEAN,
    CHAR,
    CURRENCY,
    DATA,
    DAYOFMONTH,
    EXCHANGE,
    FLOAT,
    INT,
    LENGTH,
    LOCALMKTDATE,
    MONTHYEAR,
    MULTIPLEVALUESTRING,
    PRICE,
    PRICEOFFSET,
    QTY,
    QUANTITY,
    STRING,
    UTCDATE,
    UTCTIMEONLY,
    UTCTIMESTAMP
};

const char* fix_field_type_names[] {
    "AMT",
    "BOOLEAN",
    "CHAR",
    "CURRENCY",
    "DATA",
    "DAYOFMONTH",
    "EXCHANGE",
    "FLOAT",
    "INT",
    "LENGTH",
    "LOCALMKTDATE",
    "MONTHYEAR",
    "MULTIPLEVALUESTRING",
    "PRICE",
    "PRICEOFFSET",
    "QTY",
    "QUANTITY",
    "STRING",
    "UTCDATE",
    "UTCTIMEONLY",
    "UTCTIMESTAMP"
};

const char* fix_field_cpp_types[] {
	"Decimal",
    "char",
    "char",
    "std::string",
    "std::string",
    "std::string",
    "std::string",
    "Decimal",
    "int64_t",
    "int64_t",
    "std::string",
    "std::string",
    "std::string",
    "Decimal",
    "Decimal",
    "int64_t",
    "int64_t",
    "std::string",
    "std::string",
    "std::string",
    "std::string"
};

struct FixFieldSpec {
	int number;
	std::string name;
	FixFieldType type;
	std::vector<std::string> enums;
	std::vector<std::string> descriptions;

	bool operator<(const FixFieldSpec& f1) const { return number < f1.number; }
};

void load_field_specs(const ptree &xml_spec, std::vector<FixFieldSpec> &fields, std::map<std::string,std::string> &field_length, int& chksum_field_tag) {
	const ptree& f_specs = xml_spec.get_child("fix.fields");
	bool has_next_field_length = false;
	for(const auto &pf : f_specs) {
		const ptree& f_spec = pf.second;

		// for each field spec, there is <xmlattr> describing the field and,
		// optionally, allowed values
		FixFieldSpec& f = *(fields.insert(fields.end(), FixFieldSpec()));
		for(const auto &pf2 : f_spec) {
			const ptree& f_attr = pf2.second;
			if (pf2.first=="value") {
				const ptree& v_attr = f_attr.get_child("<xmlattr>");
				f.enums.push_back(v_attr.get<std::string>("enum"));
				f.descriptions.push_back(v_attr.get<std::string>("description"));
			} else if(pf2.first=="<xmlattr>") {
				f.number = f_attr.get<int>("number");
				f.name = f_attr.get<std::string>("name");
				if (f.name == "CheckSum")
					chksum_field_tag = f.number;
				std::string stype = f_attr.get<std::string>("type");
				boost::algorithm::trim(stype);
				int type;
				for(type=0; type<FIXNFIELDTYPES; ++type) {
					if (stype==fix_field_type_names[type])
						break;
				}
				if (type == FIXNFIELDTYPES)
					throw InvalidFieldTypeException(stype);
				f.type = static_cast<FixFieldType>(type);
				if (has_next_field_length && f.type==FixFieldType::DATA)
					field_length[f.name] = (fields.end()-2)->name;
				has_next_field_length = (f.type==FixFieldType::LENGTH);
			}
		}
	}
	field_length["Signature"] = "SignatureLength";
}

void print_linear_search_validation(std::ostream& os, const FixFieldSpec& f) {
	os << "bool is_valid(const " << f.name << "& f) {\n";
	if (f.type==FixFieldType::MULTIPLEVALUESTRING) {
		os << "\tconst char* rep = f.value().c_str();\n";
		os << "\tconst char* token = rep;\n";
		os << "\tconst char* end = rep;\n";
		os << "\twhile(*end!=\'\\0\') {\n";
		os << "\t\twhile(*end!=\'\\0\' && *end!=\' \') ++end;\n";
		os << "\t\tsize_t token_len = end - token;\n";
		for(const auto &v : f.descriptions)
			os << "\t\tif ( !memcmp(token, " << f.name << '_' << v << ".c_str(), token_len) ) goto L1;\n";
		os << "\t\treturn false;\n";
		os << "\t\tL1: token = end+1;\n";
		os << "\t}\n";
		os << "\treturn true;\n";
	} else {
		for(const auto &v : f.descriptions)
			os << "\tif ( f.value() == " << f.name << '_' << v << " ) return true;\n";
		os << "\treturn false;\n";
	}
	os << "}\n\n";
}

void print_fields(std::ostream& os, const std::vector<FixFieldSpec>& fields) {
	for(const auto &f : fields) {
		os << "//----------------------------------\n\n";
		const char* fix_type = fix_field_type_names[static_cast<size_t>(f.type)];
		const char* cpp_type = fix_field_cpp_types[static_cast<size_t>(f.type)];
		os << "class " << f.name << "Traits {\n";
		os << "public:\n";
		os << "\tstatic constexpr const char* name() { return \"" << f.name << "\"; }\n";
		os << "\tstatic constexpr const char* fixtype() { return \"" << fix_type << "\"; }\n";
		os << "};\n\n";
		os << "using " << f.name << " = Field<" << cpp_type << ',' << f.number << ',' << f.name << "Traits>;\n\n";
		if(f.enums.empty())
			os << "bool is_valid(const " << f.name << "& f) { return true; }\n\n";
		else {
			char quot;
			switch(f.type) {
				case FixFieldType::BOOLEAN:
				case FixFieldType::CHAR:
					quot = '\''; break;
				case FixFieldType::AMT:
				case FixFieldType::FLOAT:
				case FixFieldType::INT:
				case FixFieldType::LENGTH:
				case FixFieldType::PRICE:
				case FixFieldType::PRICEOFFSET:
				case FixFieldType::QTY:
				case FixFieldType::QUANTITY:
					quot = '\0'; break;
				default:
					quot = '\"';
			}
			for(size_t i=0; i<f.enums.size(); ++i) {
				os << "const " << cpp_type << ' ' << f.name << '_' << f.descriptions[i] << '(';
				if (quot) os << quot;
				os << f.enums[i];
				if (quot) os << quot;
				os << ");\n";
			}
			os << '\n';
			print_linear_search_validation(os, f);
		}
	}
}


using FieldInMsg = std::pair<std::string,bool>;

struct FixMsgGroupSpec {
	size_t pos;
	FieldInMsg noxxx_field;
	std::string name;
	std::vector<FieldInMsg> fields;
	std::vector<FixMsgGroupSpec> groups;
};

struct FixMsgSpec {
	std::string name;
	std::vector<FieldInMsg> fields;
	std::vector<FixMsgGroupSpec> groups;
	FixMsgCat msgcat;
	char msgtype;
};

void load_group_spec(const ptree& g_spec, FixMsgGroupSpec& g) {
	size_t pos=0;
	for(const auto &pg : g_spec) {
		const ptree& g_attr = pg.second;
		if(pg.first=="field") {
			const ptree& f_attr = g_attr.get_child("<xmlattr>");
			g.fields.push_back(std::make_pair(f_attr.get<std::string>("name"),f_attr.get<std::string>("required")[0]=='Y'));
			++pos;
		} else if(pg.first=="<xmlattr>") {
			g.noxxx_field.first = g_attr.get<std::string>("name");
			g.noxxx_field.second = (g_attr.get<std::string>("required")[0]=='Y');
			g.name = (g.noxxx_field.first[0]=='N' ? g.noxxx_field.first.substr(2) : g.noxxx_field.first+"Group");
			// noxxx_fields.insert(g.noxxx_field.first);
		} else if(pg.first=="group") {
			FixMsgGroupSpec &g2 = *(g.groups.insert(g.groups.end(),FixMsgGroupSpec()));
			load_group_spec(g_attr, g2);
			g.fields.push_back(g2.noxxx_field);
			g2.pos = ++pos;
		}
	}
}

void load_header_or_trailer_spec(const ptree &xml_spec, FixMsgSpec &h_or_f, const char* xml_sub_tree) {
	const ptree& h_spec = xml_spec.get_child(xml_sub_tree);
	for(const auto &ph : h_spec) {
		const ptree& h_attr = ph.second;
		if (ph.first=="field") {
			const ptree& f_attr = h_attr.get_child("<xmlattr>");
			h_or_f.fields.push_back(std::make_pair(f_attr.get<std::string>("name"),f_attr.get<std::string>("required")[0]=='Y'));
		}
	}
}

void load_msg_specs(const ptree &xml_spec, std::vector<FixMsgSpec> &msgs) {
	const ptree& m_specs = xml_spec.get_child("fix.messages");
	for(const auto &pm : m_specs) {
		const ptree& m_spec = pm.second;
		FixMsgSpec& m = *(msgs.insert(msgs.end(), FixMsgSpec()));
		size_t pos=0;
		for(const auto &pm2 : m_spec) {
			const ptree& m_attr = pm2.second;
			if (pm2.first=="field") {
				const ptree& f_attr = m_attr.get_child("<xmlattr>");
				m.fields.push_back(std::make_pair(f_attr.get<std::string>("name"),f_attr.get<std::string>("required")[0]=='Y'));
				++pos;
			} else if(pm2.first=="<xmlattr>") {
				m.name = m_attr.get<std::string>("name");
				m.msgcat = (m_attr.get<std::string>("msgcat")=="admin" ? FixMsgCat::ADMIN : FixMsgCat::APP);
				m.msgtype = m_attr.get<std::string>("msgtype")[0];
			} else if(pm2.first=="group") {
				FixMsgGroupSpec &g = *(m.groups.insert(m.groups.end(), FixMsgGroupSpec()));
				load_group_spec(m_attr, g);
				m.fields.push_back(g.noxxx_field);
				g.pos = ++pos;
			}
		}
	}
}

template<typename Container, typename FieldPrinter, typename GroupPrinter>
void print_field_container(std::ostream& os, const Container& c, FieldPrinter fprn, GroupPrinter gprn) {
	std::vector<FixMsgGroupSpec>::const_iterator cg(c.groups.begin());
	size_t g_pos = (cg==c.groups.end() ? static_cast<size_t>(-1) : cg->pos);
	size_t pos;
	for(pos=0; pos<c.fields.size(); ++pos) {
		while(pos==g_pos) {
			gprn(os, *cg);
			++cg;
			g_pos = (cg==c.groups.end() ? static_cast<size_t>(-1) : cg->pos);
		}
		fprn(os, c.fields[pos]);
	}
	while(pos==g_pos) {
		gprn(os, *cg);
		++cg;
		g_pos = (cg==c.groups.end() ? static_cast<size_t>(-1) : cg->pos);
	}
}

void print_groups(std::ostream& os, const std::vector<FixMsgGroupSpec>& groups, const std::map<std::string,std::string>& field_length, const std::string& indent) {
	for(const auto &g : groups) {
		os << indent << "struct " << g.name << " {\n";
		print_groups(os, g.groups, field_length, indent+"\t");

		print_field_container (
			os, g,
			[&indent](std::ostream& os, const FieldInMsg& f){os << indent << '\t' << f.first << " f_" << f.first << ";\n";},
			[&indent](std::ostream& os, const FixMsgGroupSpec& g){os << indent << "\tstd::vector<" << g.name << "> g_" << g.name << ";\n";}
		);

		for(const auto &f : g.fields)
			os << indent << "\tbool has_" << f.first << ";\n";

		for(const auto &f : g.fields)
			os << indent << "\tstatic constexpr bool is_" << f.first << "_required() { return " << (f.second?"true":"false") << "; }\n";

		os << indent << "\tbool is_valid() const {\n";
		print_field_container (
			os, g,
			[&indent](std::ostream& os, const FieldInMsg& f){os << indent << "\t\tif (has_" << f.first << " ? !FIX::is_valid(f_" << f.first << ") : is_" << f.first << "_required()) return false;\n";},
			[&indent](std::ostream& os, const FixMsgGroupSpec& g){os << indent << "\t\tif (has_" << g.noxxx_field.first << " && (int64_t(g_" << g.name << ".size()) != f_" << g.noxxx_field.first << ".value() || !std::all_of(g_" << g.name << ".begin(), g_" << g.name << ".end(), [](const " << g.name << "& g){return g.is_valid();}))) return false;\n";}
		);
		os << indent << "\t\treturn true;\n";
		os << indent << "\t} // " << g.name << "::is_valid()\n";

		os << indent << "\tbool scan_field(size_t& field_number, const char* &buf, const char* end) {\n";
		os << indent << "\t\tbool repeat;\n";
		os << indent << "\t\tdo {\n";
		os << indent << "\t\t\trepeat = false;\n";
		os << indent << "\t\t\tswitch (field_number) {\n";
		for(const auto &f : g.fields) {
			os << indent << "\t\t\tcase " << f.first << "::number():\n";
			os << indent << "\t\t\t\tif (has_" << f.first << ")\n";
			os << indent;
			if (&f == &g.fields[0])
				os << "\t\t\t\t\treturn false;\n";
			else
				os << "\t\t\t\t\tthrow DuplicateTag(field_number);\n";
			std::map<std::string,std::string>::const_iterator pf = field_length.find(f.first);
			if (pf!=field_length.end()) {
				os << indent << "\t\t\t\tif (!has_" << pf->second << ")\n";
				os << indent << "\t\t\t\t\tthrow UnknownLength(\"" << f.first << "\");\n";
			}
			os << indent << "\t\t\t\tf_" << f.first << ".scan(buf, end";
			if (pf!=field_length.end())
				os << ", static_cast<size_t>(f_" << pf->second << ".value())";
			os << ");\n";
			os << indent << "\t\t\t\thas_" << f.first << " = true;\n";
			os << indent << "\t\t\t\treturn true;\n";
		}
		for(const auto &gg : g.groups) {
			os << indent << "\t\t\tcase " << gg.fields[0].first << "::number():\n";
			os << indent << "\t\t\t\tg_" << gg.name << ".insert(g_" << gg.name << ".end(), " << gg.name << "())->scan(field_number, buf, end);\n";
			os << indent << "\t\t\t\trepeat = true;\n";
			os << indent << "\t\t\t\tbreak;\n";
		}
		os << indent << "\t\t\t}\n";
		os << indent << "\t\t} while(repeat);\n";
		os << indent << "\t\treturn false;\n";
		os << indent << "\t} // " << g.name << "::scan_field()\n";

		os << indent << "\tvoid scan(size_t& field_number, const char* &buf, const char* end) { FIX::scan(*this, field_number, buf, end); }\n";

		os << indent << "\tvoid encode(char* &buf, char* end) const {\n";
		print_field_container (
			os, g,
			[&indent](std::ostream& os, const FieldInMsg& f){os << indent << "\t\tif(has_" << f.first << ") f_" << f.first << ".encode(buf, end);\n";},
			[&indent](std::ostream& os, const FixMsgGroupSpec& g){os << indent << "\tfor(const auto &g : g_" << g.name << ") g.encode(buf, end);\n";}
		);
		os << indent << "\t} // " << g.name << "::encode()\n";

		os << indent << "}; // " << g.name << '\n';
	}
}

void print_header(std::ostream& os, const FixMsgSpec& header, const std::map<std::string, std::string>& field_length) {
	os << "struct Header {\n";

	for(const auto &f : header.fields)
		os << '\t' << f.first << " f_" << f.first << ";\n";

	for(const auto &f : header.fields)
		os << "\tbool has_" << f.first << ";\n";

	for(const auto &f : header.fields)
		os << "\tstatic constexpr bool is_" << f.first << "_required() { return " << (f.second?"true":"false") << "; }\n";

	os << "\tbool is_valid() const {\n";
	for(const auto &f : header.fields)
		os << "\t\tif (has_" << f.first << " ? !FIX::is_valid(f_" << f.first << ") : is_" << f.first << "_required()) return false;\n";
	os << "\t\treturn true;\n";
	os << "\t} // Header::is_valid()\n";

	os << "\tvoid clear() {\n";
	for(const auto &f : header.fields)
		os << "\t\thas_" << f.first << " = false;\n";
	os << "\t} // Header::clear()\n";

	os << "\tbool scan_field(size_t field_number, const char* &buf, const char* end) {\n";
	os << "\t\tswitch (field_number) {\n";
	for(const auto &f : header.fields) {
		os << "\t\tcase " << f.first << "::number():\n";
		os << "\t\t\tif (has_" << f.first << ")\n";
		os << "\t\t\t\tthrow DuplicateTag(field_number);\n";
		std::map<std::string,std::string>::const_iterator pf = field_length.find(f.first);
		if (pf!=field_length.end()) {
			os << "\t\t\tif (!has_" << pf->second << ")\n";
			os << "\t\t\t\tthrow UnknownLength(\"" << f.first << "\");\n";
		}
		os << "\t\t\tf_" << f.first << ".scan(buf, end";
		if (pf!=field_length.end())
			os << ", static_cast<size_t>(f_" << pf->second << ".value())";
		os << ");\n";
		os << "\t\t\thas_" << f.first << " = true;\n";
		os << "\t\t\treturn true;\n";
	}
	os << "\t\t}\n";
	os << "\t\treturn false;\n";
	os << "\t} // Header::scan_field()\n";

	os << "\tvoid scan(size_t& field_number, const char* &buf, const char* end) {\n";
	os << "\t\tclear();\n";
	os << "\t\tFIX::scan(*this, field_number, buf, end);\n";
	os << "\t}\n";

	os << "\tvoid encode(char* &buf, char* end) const {\n";
	for(const auto &f : header.fields)
		os << "\t\tif(has_" << f.first << ") f_" << f.first << ".encode(buf, end);\n";
	os << "\t} // Header::encode()\n";

	os << "}; // Header\n\n";
}

void print_trailer(std::ostream& os, const FixMsgSpec& trailer, const std::map<std::string,std::string>& field_length, uint8_t last_tag_chksum) {
	os << "struct Trailer {\n";

	for(const auto &f : trailer.fields)
		os << '\t' << f.first << " f_" << f.first << ";\n";

	for(const auto &f : trailer.fields)
		os << "\tbool has_" << f.first << ";\n";

	os << "\tconst char* msg_buf_begin;\n";

	for(const auto &f : trailer.fields)
		os << "\tstatic constexpr bool is_" << f.first << "_required() { return " << (f.second?"true":"false") << "; }\n";

	os << "\tbool is_valid() const {\n";
	for(const auto &f : trailer.fields)
		os << "\t\tif (has_" << f.first << " ? !FIX::is_valid(f_" << f.first << ") : is_" << f.first << "_required()) return false;\n";
	os << "\t\treturn true;\n";
	os << "\t} // Trailer::is_valid()\n";

	os << "\tvoid clear() {\n";
	for(const auto &f : trailer.fields)
		os << "\t\thas_" << f.first << " = false;\n";
	os << "\t} // Trailer::clear()\n";

	os << "\tvoid validate_chksum(const char* &buf, const char* end) {\n";
	os << "\t\tuint8_t s_expected = msg_chksum(msg_buf_begin, buf-1) - uint8_t(" << int(last_tag_chksum) << ");\n";
	os << "\t\tf_CheckSum.scan(buf, end);\n";
	os << "\t\thas_CheckSum = true;\n";
	os << "\t\tuint8_t s_received = boost::lexical_cast<uint16_t>(f_CheckSum.value());\n";
	os << "\t\tif (s_expected != s_received)\n";
	os << "\t\t\tthrow InvalidChksum(s_expected, s_received);\n";
	os << "\t} // Trailer::validate_chksum()\n";

	os << "\tbool scan_field(size_t field_number, const char* &buf, const char* end) {\n";
	os << "\t\tswitch (field_number) {\n";
	for(const auto &f : trailer.fields) {
		os << "\t\tcase " << f.first << "::number():\n";
		if (f.first=="CheckSum") {
			os << "\t\t\tvalidate_chksum(buf, end);\n";
			os << "\t\t\thas_CheckSum = true;\n";
			os << "\t\t\treturn false;\n";
		} else {
			os << "\t\t\tif (has_" << f.first << ")\n";
			os << "\t\t\t\tthrow DuplicateTag(field_number);\n";
			std::map<std::string,std::string>::const_iterator pf = field_length.find(f.first);
			if (pf!=field_length.end()) {
				os << "\t\t\tif (!has_" << pf->second << ")\n";
				os << "\t\t\t\tthrow UnknownLength(\"" << f.first << "\");\n";
			}
			os << "\t\t\tf_" << f.first << ".scan(buf, end";
			if (pf!=field_length.end())
				os << ", static_cast<size_t>(f_" << pf->second << ".value())";
			os << ");\n";
			os << "\t\t\thas_" << f.first << " = true;\n";
			os << "\t\t\treturn true;\n";
		}
	}
	os << "\t\t}\n";
	os << "\t\treturn false;\n";
	os << "\t} // Trailer::scan_field()\n";

	os << "\tvoid scan(size_t& field_number, const char* begin, const char* &buf, const char* end) {\n";
	os << "\t\tclear();\n";
	os << "\t\tmsg_buf_begin = begin;\n";
	os << "\t\tFIX::scan(*this, field_number, buf, end);\n";
	os << "\t}\n";

	os << "\tvoid encode(char* begin, char* &buf, char* end) {\n";
	for(const auto &f : trailer.fields) {
		if (f.first=="CheckSum") {
			os << "\t\tf_CheckSum.value() = boost::lexical_cast<std::string>(uint16_t(msg_chksum(msg_buf_begin=begin, buf)));\n";
			os << "\t\thas_CheckSum = true;\n";
			os << "\t\tf_CheckSum.encode(buf, end);\n";
		} else
			os << "\t\tif(has_" << f.first << ") f_" << f.first << ".encode(buf, end);\n";
	}
	os << "\t} // Trailer::encode()\n";

	os << "}; // Trailer\n\n";
}

void print_msgs(std::ostream& os, const std::vector<FixMsgSpec>& msgs, const std::map<std::string,std::string>& field_length) {
	for(const auto &m : msgs) {
		os << "struct " << m.name << " {\n";
		print_groups(os, m.groups, field_length, "\t");

		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInMsg& f){os << '\t' << f.first << " f_" << f.first << ";\n";},
			[](std::ostream& os, const FixMsgGroupSpec& g){os << "\tstd::vector<" << g.name << "> g_" << g.name << ";\n";}
		);

		for(const auto &f : m.fields)
			os << "\tbool has_" << f.first << ";\n";

		for(const auto &f : m.fields)
			os << "\tstatic constexpr bool is_" << f.first << "_required() { return " << (f.second?"true":"false") << "; }\n";

		os << "\tbool is_valid() const {\n";
		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInMsg& f){os << "\t\tif (has_" << f.first << " ? !FIX::is_valid(f_" << f.first << ") : is_" << f.first << "_required()) return false;\n";},
			[](std::ostream& os, const FixMsgGroupSpec& g){os << "\t\tif (has_" << g.noxxx_field.first << " && (int64_t(g_" << g.name << ".size()) != f_" << g.noxxx_field.first << ".value() || !std::all_of(g_" << g.name << ".begin(), g_" << g.name << ".end(), [](const " << g.name << "& g){return g.is_valid();}))) return false;\n";}
		);
		os << "\t\treturn true;\n";
		os << "\t} // " << m.name << "::is_valid()\n";

		os << "\tvoid clear() {\n";
		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInMsg& f){os << "\t\thas_" << f.first << " = false;\n";},
			[](std::ostream& os, const FixMsgGroupSpec& g){os << "\t\t" << "g_" << g.name << ".clear();\n";}
		);
		os << "\t} // " << m.name << "::clear()\n";

		os << "\tbool scan_field(size_t& field_number, const char* &buf, const char* end) {\n";
		os << "\t\tbool repeat;\n";
		os << "\t\tdo {\n";
		os << "\t\t\trepeat = false;\n";
		os << "\t\t\tswitch (field_number) {\n";
		for(const auto &f : m.fields) {
			os << "\t\t\tcase " << f.first << "::number():\n";
			os << "\t\t\t\tif (has_" << f.first << ")\n";
			os << "\t\t\t\t\tthrow DuplicateTag(field_number);\n";
			std::map<std::string,std::string>::const_iterator pf = field_length.find(f.first);
			if (pf!=field_length.end()) {
				os << "\t\t\t\tif (!has_" << pf->second << ")\n";
				os << "\t\t\t\t\tthrow UnknownLength(\"" << f.first << "\");\n";
			}
			os << "\t\t\t\tf_" << f.first << ".scan(buf, end";
			if (pf!=field_length.end())
				os << ", static_cast<size_t>(f_" << pf->second << ".value())";
			os << ");\n";
			os << "\t\t\t\thas_" << f.first << " = true;\n";
			os << "\t\t\t\treturn true;\n";
		}
		for(const auto &g : m.groups) {
			os << "\t\t\tcase " << g.fields[0].first << "::number():\n";
			os << "\t\t\t\tg_" << g.name << ".insert(g_" << g.name << ".end(), " << g.name << "())->scan(field_number, buf, end);\n";
			os << "\t\t\t\trepeat = true;\n";
			os << "\t\t\t\tbreak;\n";
		}
		os << "\t\t\t}\n";
		os << "\t\t} while(repeat);\n";
		os << "\t\treturn false;\n";
		os << "\t} // " << m.name << "::scan_field()\n";

		os << "\tvoid scan(size_t& field_number, const char* &buf, const char* end) {\n";
		os << "\t\tclear();\n";
		os << "\t\tFIX::scan(*this, field_number, buf, end);\n";
		os << "\t}\n";

		os << "\tvoid encode(char* &buf, char* end) const {\n";
		print_field_container (
			os, m,
			[](std::ostream& os, const FieldInMsg& f){os << "\t\tif(has_" << f.first << ") f_" << f.first << ".encode(buf, end);\n";},
			[](std::ostream& os, const FixMsgGroupSpec& g){os << "\t\tfor(const auto &g : g_" << g.name << ") g.encode(buf, end);\n";}
		);
		os << "\t} // " << m.name << "::encode()\n";

		os << "\tstatic constexpr char msgtype() { return \'" << m.msgtype << "\'; }\n";
		os << "\tstatic constexpr bool is_admin() { return " << (m.msgcat==FixMsgCat::ADMIN ? "true" : "false") << "; }\n";
		os << "\tstatic constexpr bool is_app() { return " << (m.msgcat==FixMsgCat::APP ? "true" : "false") << "; }\n";

		os << "}; // " << m.name << "\n\n";
	}
}

void print_handler(std::ostream &os, const FixMsgSpec& header, const FixMsgSpec& trailer, const std::vector<FixMsgSpec>& msgs) {
	os << "class Handler {\n";
	os << "public:\n";
	os << "\tHeader header_;\n";
	os << "\tTrailer trailer_;\n";
	for(const auto &m : msgs)
		os << '\t' << m.name << " m_" << m.name << "_;\n";
	for(const auto &m : msgs)
		os << "\tvirtual void on_" << m.name << "_received(const Header& header, const " << m.name << "& m_" << m.name << ", const Trailer& trailer) { }\n";

	os << "\tvoid scan(const char* begin, const char* end) {\n";
	os << "\t\tconst char* buf(begin);\n";
	os << "\t\tsize_t field_number = scan_tag(buf, end);\n";
	os << "\t\tif (field_number!=" << header.fields[0].first << "::number())\n";
	os << "\t\t\tthrow UnexpectedHeader(field_number);\n";
	os << "\t\theader_.scan(field_number, buf, end);\n";
	os << "\t\tif (!header_.has_MsgType)\n";
	os << "\t\t\tthrow UnknownMessageType();\n";
	os << "\t\tchar msgtype = header_.f_MsgType.value()[0];\n";
	os << "\t\tswitch(msgtype) {\n";
	for(const auto &m : msgs) {
		os << "\t\tcase " << m.name << "::msgtype():\n";
		os << "\t\t\tm_" << m.name <<"_.scan(field_number, buf, end);\n";
		os << "\t\t\tbreak;\n";
	}
	os << "\t\t}\n";
	os << "\t\ttrailer_.scan(field_number, begin, buf, end);\n";
	os << "\t\tif (field_number!=CheckSum::number())\n";
	os << "\t\t\tthrow UnexpectedTag(field_number);\n";
	os << "\t\tswitch(msgtype) {\n";
	for(const auto &m : msgs) {
		os << "\t\tcase " << m.name << "::msgtype():\n";
		os << "\t\t\ton_" << m.name <<"_received(header_, m_" << m.name << "_, trailer_);\n";
		os << "\t\t\tbreak;\n";
	}
	os << "\t\t}\n";
	os << "\t} // Handler::scan()\n";

	for(const auto &m : msgs) {
		os << "\tvoid encode_" << m.name << "(char* &buf, char* end) {\n";
		os << "\t\tchar* begin(buf);\n";
		os << "\t\theader_.encode(buf, end);\n";
		os << "\t\tm_" << m.name << "_.encode(buf, end);\n";
		os << "\t\ttrailer_.encode(begin, buf, end);\n";
		os << "\t} // Handler::encode_" << m.name << "()\n";
	}

	os << "}; // Handler\n";
}

uint8_t chksum(int tag) {
	uint8_t result = 0;
	while (tag>0) {
		div_t d = div(tag,10);
		result += static_cast<uint8_t>('0') + static_cast<uint8_t>(d.rem);
		tag = d.quot;
	}
	return result;
}

void fix_xml_compiler(std::ostream &os, const std::string& xml_file) {
	ptree xml_spec;
	read_xml(xml_file, xml_spec);

	os << "// Code generated from " << xml_file << "\n\n";
	os << "#ifndef FIX_COMPILED_H_\n";
	os << "#define FIX_COMPILED_H_\n\n";
	os << "#include <cstdint>\n";
	os << "#include <string>\n";
	os << "#include <vector>\n";
	os << "#include <algorithm>\n";
	os << "#include <boost/lexical_cast.hpp>\n";
	os << "#include \"message.h\"\n";
	os << "#include \"utils.h\"\n\n";
	os << "namespace FIX {\n\n";

	std::vector<FixFieldSpec> fields;
	std::map<std::string,std::string> field_length;
	int chksum_field_tag;
	load_field_specs(xml_spec, fields, field_length, chksum_field_tag);
	print_fields(os, fields);

	os << "//----------------------------------\n\n";

	FixMsgSpec header, trailer;
	std::vector<FixMsgSpec> msgs;

	load_header_or_trailer_spec(xml_spec, header, "fix.header");
	load_header_or_trailer_spec(xml_spec, trailer, "fix.trailer");
	load_msg_specs(xml_spec, msgs);

	print_header(os, header, field_length);
	print_trailer(os, trailer, field_length, chksum(chksum_field_tag));
	print_msgs(os, msgs, field_length);

	print_handler(os, header, trailer, msgs);

	os << "\n}\n\n";
	os << "\n#endif\t// FIX_COMPILED_H_\n";
}


int main(int argc, char** argv) {
	if (argc==3) {
		std::ofstream os(argv[2]);
		fix_xml_compiler(os, argv[1]);
		os.close();
	} else
		std::cout << "Usage: fix_compiler <fix8_template_file> <cpp_header_output_file>\n";
	return 0;
}
