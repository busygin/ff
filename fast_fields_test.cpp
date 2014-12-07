#include <string>

#include "optional.h"
#include "message.h"
#include "utils.h"
#include "fast_fields.h"
#include "fast_test.h"


class TestFastHandler : public FIX::BaseFastHandler {
  Optional<std::string> template1_text_;
public:
  void on_template1(const FIX::template1& m_template1) {
    if (m_template1.f_Text.defined())
      template1_text_ = m_template1.f_Text.value();
    else
      template1_text_.disable();
  }
  bool get_value(std::string& v) {
    if (template1_text_) {
      v = *template1_text_;
      return true;
    } else return false;
  }
};

TestFastHandler fast_handler;
FIX::FastParser<TestFastHandler> fast_parser(fast_handler);


const char* fast_m1 = "\xE0\x81\x48\x65\x6C\x6C\x6F\x57\x6F\x72\x6C\xE4";


int main(int argc, char **argv) {
	fast_parser.scan(fast_m1, fast_m1+12);
	std::string str;
	fast_handler.get_value(str);
	std::cout << str << std::endl;

	char buf[256];
	char* end = buf+256;
	char* p(buf);
	fast_parser.encode_template1(p, end);
	std::cout << std::hex;
	for(char* p1=buf; p1<p; ++p1) std::cout << (*p1 & int(255)) << ' ';
	std::cout << std::endl;

	Optional<std::string> a("");
	p = buf;
	FIX::fast_encode_with_null(a, p, end);
	for(char* p1=buf; p1<p; ++p1) std::cout << (*p1 & int(255)) << ' ';
	std::cout << std::dec << std::endl;
	const char* p1 = buf;
	FIX::fast_scan_with_null(a, p1, end);
	std::cout << *a << std::endl;

	FIX::NoOperatorOptionalField<int64_t,33> f0;
	Optional<int64_t> v(65535);
	p = buf;
	FIX::PMap pmap;
	f0.encode(v, p, end, pmap);
	f0.reset();
	pmap.reset();
	p1 = buf;
	v = 0;
	v.disable();
	f0.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;

	FIX::ConstantMandatoryField<int64_t,34> fc(-65536);
	p = buf;
	pmap.clear();
	v = -65536;
	fc.encode(v, p, end, pmap);
	fc.reset();
	pmap.reset();
	p1 = buf;
	v = 0;
	v.disable();
	fc.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;

	FIX::CopyMandatoryField<int64_t,35> fp;
	v = 32768;
	p = buf;
	pmap.clear();
	fp.encode(v, p, end, pmap);
	fp.encode(v, p, end, pmap);
	fp.reset();
	pmap.reset();
	p1 = buf;
	v = 0;
	v.disable();
	fp.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;
	v = 0;
	v.disable();
	fp.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;

	FIX::DefaultMandatoryField<int64_t,35> fd(255);
	v = 255;
	p = buf;
	pmap.clear();
	fd.encode(v, p, end, pmap);
	v = -256;
	fd.encode(v, p, end, pmap);
	fd.reset();
	pmap.reset();
	p1 = buf;
	v = 0;
	v.disable();
	fd.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;
	v = 0;
	v.disable();
	fd.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;

	FIX::DeltaMandatoryField<int64_t,35> fl;
	v = 127;
	p = buf;
	pmap.clear();
	fl.encode(v, p, end, pmap);
	v = 128;
	fl.encode(v, p, end, pmap);
	fl.reset();
	pmap.reset();
	p1 = buf;
	v = 0;
	v.disable();
	fl.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;
	v = 0;
	v.disable();
	fl.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;

	FIX::IncrementMandatoryField<int64_t,111> fi;
	v = 85431;
	p = buf;
	pmap.clear();
	fi.encode(v, p, end, pmap);
	v = 85434;
	fi.encode(v, p, end, pmap);
	fi.reset();
	pmap.reset();
	p1 = buf;
	v = 0;
	v.disable();
	fi.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;
	v = 0;
	v.disable();
	fi.scan(v, p1, p, pmap);
	std::cout << *v << std::endl;

	return 0;
}
