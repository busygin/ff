#include <cstring>
#include <string>
#include <boost/lexical_cast.hpp>

#include "optional.h"
#include "message.h"
#include "utils.h"
#include "fix42.h"
#include "fast_fields.h"
#include "fast_test.h"

#include "gtest/gtest.h"


class TestHandler : public FIX::Handler {
  bool valid_;
public:
  virtual void on_Logon_received(const FIX::Header& header, const FIX::Logon& m_Logon, const FIX::Trailer& trailer) {
    valid_ = m_Logon.is_valid();
  }
  virtual void on_News_received(const FIX::Header& header, const FIX::News& m_News, const FIX::Trailer& trailer) {
    valid_ = m_News.is_valid();
  }
  bool is_valid() const { return valid_; }
};


TestHandler handler;

const char* m1 = "8=FIX.4.2\0019=72\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\0011234=blah\00198=0\00110=094\001";
const char* m1_1 = "8=FIX.4.2\0019=12\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00198=0\00110=185\001";

const char* m2 = "8=FIX.4.2\0019=173\00135=B\00149=A12345B\00156=COMPARO\00134=78\00150=2DEFGH4\001"
	"52=20131125-02:19:46.108\001148=Here is the nws\00133=4\00158=The rain in Spain\001"
	"58=stays mainly\00158=on the plain\00158=End bulletin\0011234=blah\00110=135\001";
const char* m2_1 = "8=FIX.4.2\0019=173\00135=B\00149=A12345B\00156=COMPARO\00134=78\00150=2DEFGH4\001"
	"52=20131125-02:19:46.108\001148=Here is the nws\00133=4\00158=The rain in Spain\001"
	"58=stays mainly\00158=on the plain\00158=End bulletin\00110=232\001";

const char* m3 = "8=FIX.4.2\0019=62\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00198=0\00110=094\001";
const char* m3_1 = "8=FIX.4.2\0019=62\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00198=0\00110=190\001";

const char* m4 = "8=FIX.4.2\0019=12\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00198=0\00110=097\001";

const char* m5 = "8=FIX.4.2\0019=62\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00110=223\001";

const char* m6 = "8=FIX.4.2\0019=62\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00198=0\00189=I hereby\001sertify this logon\00110=190\001";
const char* m6_1 = "8=FIX.4.2\0019=62\00135=A\00134=1\00149=CLIENT\00156=SERVER\00152=20130304-02:44:30\001108=30\00198=0\00193=27\00189=I hereby\001sertify this logon\00110=134\001";


TEST(decimal, conversions)
{
  char buf[1024];
  char* p;
  FIX::Decimal a;

  a.mantissa = 4;
  a.exponent = -4;
  p = buf;
  FIX::fixcopy(p,a);
  EXPECT_EQ(boost::lexical_cast<double>(buf, p-buf), 0.0004);
  EXPECT_EQ(a.to_double(), 0.0004);
  a.mantissa = a.exponent = 0;
  FIX::fixscan(a, buf, p);
  EXPECT_EQ(a.to_double(), 0.0004);

  a.mantissa = -54;
  a.exponent = -4;
  p = buf;
  FIX::fixcopy(p,a);
  EXPECT_EQ(boost::lexical_cast<double>(buf, p-buf), -0.0054);
  EXPECT_EQ(a.to_double(), -0.0054);
  a.mantissa = a.exponent = 0;
  FIX::fixscan(a, buf, p);
  EXPECT_EQ(a.to_double(), -0.0054);

  a.mantissa = -21;
  a.exponent = 0;
  p = buf;
  FIX::fixcopy(p,a);
  EXPECT_EQ(boost::lexical_cast<double>(buf, p-buf), -21);
  EXPECT_EQ(a.to_double(), -21);
  a.mantissa = a.exponent = 0;
  FIX::fixscan(a, buf, p);
  EXPECT_EQ(a.to_double(), -21);

  a.mantissa = 0;
  a.exponent = 0;
  p = buf;
  FIX::fixcopy(p,a);
  EXPECT_EQ(boost::lexical_cast<double>(buf, p-buf), 0);
  EXPECT_EQ(a.to_double(), 0);
  a.mantissa = a.exponent = 1;
  FIX::fixscan(a, buf, p);
  EXPECT_EQ(a.to_double(), 0);

  a.mantissa = 11;
  a.exponent = 3;
  p = buf;
  FIX::fixcopy(p,a);
  EXPECT_EQ(boost::lexical_cast<double>(buf, p-buf), 11000);
  EXPECT_EQ(a.to_double(), 11000);
  a.mantissa = a.exponent = 0;
  FIX::fixscan(a, buf, p);
  EXPECT_EQ(a.to_double(), 11000);
}

TEST(message, unknown_field)
{
  // tag 1234 is undefined
  EXPECT_NO_THROW(handler.scan(m1_1, m1_1+strlen(m1_1)));
  EXPECT_TRUE(handler.is_valid());
  EXPECT_THROW(handler.scan(m1, m1+strlen(m1)), FIX::UnexpectedTag);
}

TEST(message, unknown_field_repeating_group)
{
  // tag 1234 is undefined
  EXPECT_NO_THROW(handler.scan(m2_1, m2_1+strlen(m2_1)));
  EXPECT_TRUE(handler.is_valid());
  EXPECT_THROW(handler.scan(m2, m2+strlen(m2)), FIX::UnexpectedTag);
}

TEST(message, chksum_checking)
{
  // chksum is wrong
  EXPECT_NO_THROW(handler.scan(m3_1, m3_1+strlen(m3_1)));
  EXPECT_TRUE(handler.is_valid());
  EXPECT_THROW(handler.scan(m3, m3+strlen(m3)), FIX::InvalidChksum);
}

TEST(message, missing_message_type)
{
  // missing tag 35 in header
  EXPECT_THROW(handler.scan(m4, m4+strlen(m4)), FIX::UnknownMessageType);
}

TEST(message, missing_required_field)
{
  // missing tag 98 in Logon message
  EXPECT_NO_THROW(handler.scan(m5, m5+strlen(m5)));
  EXPECT_FALSE(handler.is_valid());
}

TEST(message, decoding_fields)
{
  EXPECT_NO_THROW(handler.scan(m3_1, m3_1+strlen(m3_1)));
  EXPECT_TRUE(handler.is_valid());
  EXPECT_TRUE(handler.m_Logon_.f_HeartBtInt.value() == 30);
  EXPECT_TRUE(handler.m_Logon_.f_EncryptMethod.value() == 0);
}

TEST(message, binary_data_fields)
{
  // missing SignatureLength (tag 93) in trailer
  EXPECT_NO_THROW(handler.scan(m6_1, m6_1+strlen(m6_1)));
  EXPECT_TRUE(handler.is_valid());
  EXPECT_THROW(handler.scan(m6, m6+strlen(m6)), FIX::UnknownLength);
}

TEST(message, encoding)
{
  size_t m6_len = strlen(m6_1);
  EXPECT_NO_THROW(handler.scan(m6_1, m6_1+m6_len));
  char buf[1024];
  char* p(buf);
  EXPECT_NO_THROW(handler.encode_Logon(p, p+1024));
  size_t encoded_len = p-buf;
  EXPECT_EQ(m6_len, encoded_len);
  EXPECT_EQ(FIX::msg_chksum(buf, buf+m6_len), FIX::msg_chksum(m6_1, m6_1+m6_len));
}

TEST(fast, stopbit_decoding)
{
  char str[] = "Hello FAST!";
  size_t len = strlen(str);
  str[len-1] |= '\x80';
  const char* buf = str;
  const char* end = buf+len;
  Optional<std::string> value;
  EXPECT_NO_THROW(FIX::fast_scan_with_null(value, buf, end));
  EXPECT_EQ(*value, "Hello FAST!");

  // NULL support for strings
  char str_null_then_empty[] = "\x80\x00\x80";
  buf = str_null_then_empty;
  end = buf + 3;
  EXPECT_NO_THROW(FIX::fast_scan_with_null(value, buf, end));
  EXPECT_FALSE(value);
  EXPECT_NO_THROW(FIX::fast_scan_with_null(value, buf, end));
  EXPECT_TRUE(bool(value));
  EXPECT_EQ(*value, "");

  char ui0[] = "\x80";
  char ui639[] = "\x04\xFF";
  char ui0ui639ui0[] = "\x80\x04\xFF\x80";
  end = ui0ui639ui0 + 4;
  uint64_t u;
  EXPECT_NO_THROW(FIX::unsigned_fast_scan_without_null(u, buf=ui0, ui0+1));
  EXPECT_EQ(u, 0);
  EXPECT_NO_THROW(FIX::unsigned_fast_scan_without_null(u, buf=ui639, ui639+2));
  EXPECT_EQ(u, 639);
  EXPECT_NO_THROW(FIX::unsigned_fast_scan_without_null(u, buf=ui0ui639ui0, end));
  EXPECT_EQ(u, 0);
  EXPECT_NO_THROW(FIX::unsigned_fast_scan_without_null(u, buf, end));
  EXPECT_EQ(u, 639);
  EXPECT_NO_THROW(FIX::unsigned_fast_scan_without_null(u, buf, end));
  EXPECT_EQ(u, 0);

  char i63[] = "\xBF";
  char im1[] = "\xFF";
  char im2[] = "\xFE";
  char im64[] = "\xC0";
  char i_seq[] = "\xBF\x08\x00\x00\x00\x80\x78\x00\x00\x00\x80\xC0";
  end = i_seq + 12;
  int32_t i;
  EXPECT_NO_THROW(FIX::signed_fast_scan_without_null(i, buf=i63, i63+1));
  EXPECT_EQ(i, 63);
  EXPECT_NO_THROW(FIX::signed_fast_scan_without_null(i, buf=im1, im1+1));
  EXPECT_EQ(i, -1);
  EXPECT_NO_THROW(FIX::signed_fast_scan_without_null(i, buf=im2, im2+1));
  EXPECT_EQ(i, -2);
  EXPECT_NO_THROW(FIX::signed_fast_scan_without_null(i, buf=im64, im64+1));
  EXPECT_EQ(i, -64);
  EXPECT_NO_THROW(FIX::signed_fast_scan_without_null(i, buf=i_seq, end));
  EXPECT_EQ(i, 63);
  Optional<int64_t> j;
  EXPECT_NO_THROW(FIX::signed_fast_scan_with_null(j, buf, end));
  EXPECT_EQ(*j, (int64_t(1)<<31)-1);
  EXPECT_NO_THROW(FIX::signed_fast_scan_with_null(j, buf, end));
  EXPECT_EQ(*j, -(int64_t(1)<<31));
  EXPECT_NO_THROW(FIX::signed_fast_scan_with_null(j, buf, end));
  EXPECT_EQ(*j, -64);
}


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


TEST(fast, hello_world_template1)
{
  const char* fast_m1_begin(fast_m1);
  EXPECT_NO_THROW(fast_parser.scan(fast_m1, fast_m1+12));
  std::string str;
  EXPECT_TRUE(fast_handler.get_value(str));
  EXPECT_EQ(str,"HelloWorld");

  // Here is how message is created for encoding
  // (assigning Text field of template1 to "HelloWorlD")
  fast_parser.m_template1_.set_Text("HelloWorlD");

  char buf[256];
  char* end(buf+256);
  char* p(buf);
  EXPECT_NO_THROW(fast_parser.encode_template1(p, end));
  size_t len = p-buf;
  EXPECT_NE(memcmp(fast_m1_begin, buf, len), 0);

  fast_parser.m_template1_.set_Text("HelloWorld");
  EXPECT_NO_THROW(fast_parser.encode_template1(p=buf, end));
  len = p-buf;
  EXPECT_EQ(memcmp(fast_m1_begin, buf, len), 0);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
