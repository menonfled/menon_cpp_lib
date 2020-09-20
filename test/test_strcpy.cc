#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstring>
#include <cwchar>

int main()
{
  using namespace std::literals;

  std::string s = "abcdefghi";
  std::string sbuf;
  char buf[5];
  wchar_t wbuf[5];

  {
    BOOST_TEST_EQ(menon::strcpy(buf, 0, "abc"), buf);
    BOOST_TEST_EQ(menon::strcpy((char*)nullptr, 0, "abc"), nullptr);

    BOOST_TEST_CSTR_EQ(menon::strcpy(buf, s), "abcd");
    BOOST_TEST_CSTR_EQ(menon::strcpy(&buf[0], 4, s), "abc");

    BOOST_TEST_EQ(menon::strcpy(sbuf, s), s);

    BOOST_TEST_EQ(std::wcscmp(menon::strcpy(wbuf, L"abcdefg"), L"abcd"), 0);

    BOOST_TEST_THROWS(menon::strcpy((char*)nullptr, 3, "abc"), std::invalid_argument);
  }

  {
    BOOST_TEST_EQ(std::memcmp(menon::strncpy(buf, s, 3), s.c_str(), 3), 0);
    std::memset(buf, 0xff, 5);
    BOOST_TEST_EQ(std::memcmp(menon::strncpy(buf, "abc", 5), "abc\0\0", 5), 0);

    BOOST_TEST_EQ(std::wmemcmp(menon::strncpy(wbuf, L"abcdef", 3), L"abc", 3), 0);

    BOOST_TEST_THROWS(menon::strncpy((char*)nullptr, "abc", 5), std::invalid_argument);
  }
  return boost::report_errors();
}
