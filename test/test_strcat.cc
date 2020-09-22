#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstring>
#include <cwchar>

int main()
{
  using namespace std::literals;

  std::string s = "abcdefghi";
  std::string sbuf;

  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strcat(s, 16, "def"), "abcdef");
  }
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strcat(s, "def"), "abcdef");
  }
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strcat(wcs, 16, L"def"), L"abcdef"), 0);
  }
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strcat(wcs, L"def"), L"abcdef"), 0);
  }
  {
    std::string str = "abc";
    BOOST_TEST_EQ(menon::strcat(str, "def"), "abcdef");

    std::wstring wstr = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strcat(wstr, L"def").c_str(), L"abcdef"), 0);
  }
  return boost::report_errors();
}
