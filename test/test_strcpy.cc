#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cwchar>

int main()
{
  using namespace std::literals;

  std::string s = "abcdefghi";
  char buf[5];
  wchar_t wbuf[5];

  BOOST_TEST_EQ(menon::strcpy(buf, 0, "abc"), buf);
  BOOST_TEST_EQ(menon::strcpy((char*)nullptr, 0, "abc"), nullptr);

  BOOST_TEST_CSTR_EQ(menon::strcpy(buf, s), "abcd");
  BOOST_TEST_CSTR_EQ(menon::strcpy(&buf[0], 4, s), "abc");

  BOOST_TEST_EQ(std::wcscmp(menon::strcpy(wbuf, L"abcdefg"), L"abcd"), 0);

  return boost::report_errors();
}
