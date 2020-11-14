// test_strcat.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstring>
#include <cwchar>

// strcat関数のテストコード
void test_strcat()
{
  using namespace std::literals;

  // char文字列の場合
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strcat(s, 16, "def"), "abcdef");
  }
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strcat(s, "def"), "abcdef");
  }

  // wchar_t文字列の場合
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strcat(wcs, 16, L"def"), L"abcdef"), 0);
  }
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strcat(wcs, L"def"), L"abcdef"), 0);
  }

  // stringの場合
  {
    std::string str = "abc";
    BOOST_TEST_EQ(menon::strcat(str, "def"), "abcdef");

    std::wstring wstr = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strcat(wstr, L"def").c_str(), L"abcdef"), 0);
  }
}

// strncat関数のテストコード
void test_strncat()
{
  using namespace std::literals;

  // char文字列の場合
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strncat(s, 16, "defghi", 3), "abcdef");
  }
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strncat(s, 16, "def", 5), "abcdef");
  }
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strncat(s, "defghi", 3), "abcdef");
  }
  {
    char s[16] = "abc";
    BOOST_TEST_CSTR_EQ(menon::strncat(s, "def", 5), "abcdef");
  }

  // wchar_t文字列の場合
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strncat(wcs, 16, L"defghi", 3), L"abcdef"), 0);
  }
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strncat(wcs, L"defghi", 3), L"abcdef"), 0);
  }
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strncat(wcs, 16, L"def", 5), L"abcdef"), 0);
  }
  {
    wchar_t wcs[16] = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strncat(wcs, L"def", 5), L"abcdef"), 0);
  }

  // stringの場合
  {
    std::string str = "abc";
    BOOST_TEST_EQ(menon::strncat(str, "defghi", 3), "abcdef");

    std::wstring wstr = L"abc";
    BOOST_TEST_EQ(std::wcscmp(menon::strncat(wstr, L"defghi", 3).c_str(), L"abcdef"), 0);
  }
}

int main()
{
  test_strcat();
  test_strncat();
  return boost::report_errors();
}
