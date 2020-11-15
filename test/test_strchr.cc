﻿// test_strchr.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cwchar>
#include <iostream>

// strchr関数のテストコード
void test_strchr()
{
  using namespace std::literals;

  { // char配列版
    constexpr auto s = "abcdefg";
    constexpr auto it = menon::strchr(s, 'd');
    BOOST_TEST_EQ(it, &s[3]);
    BOOST_TEST_EQ(menon::strchr(&s[0], 'd'), &s[3]);
    BOOST_TEST_EQ(menon::strchr(const_cast<char const*>(&s[0]), 'd'), &s[3]);
    BOOST_TEST_EQ(menon::strchr(s, 'x'), nullptr);
  }
  { // string_view版
    constexpr auto s = "abcdefg"sv;
    constexpr auto it = menon::strchr(s, 'd');
    BOOST_TEST_EQ(it, s.begin() + 3);
    BOOST_TEST_EQ(menon::strchr(s, 'x'), decltype(s.begin())());
  }
  { // string版
    auto s = "abcdefg"s;
    auto it = menon::strchr(s, 'd');
    BOOST_TEST(it == s.begin() + 3);
    BOOST_TEST(menon::strchr(s, 'x') == decltype(s.begin())());
  }

  { // wchar_t配列版
    constexpr auto s = L"abcdefg";
    constexpr auto it = menon::strchr(s, L'd');
    BOOST_TEST(it == &s[3]);
    BOOST_TEST(menon::strchr(&s[0], L'd') == &s[3]);
    BOOST_TEST(menon::strchr(s, L'x') == nullptr);
  }
  { // wchar_t配列とchar文字版
    constexpr auto s = L"abcdefg";
    constexpr auto it = menon::strchr(s, 'd');
    BOOST_TEST(it == &s[3]);
    BOOST_TEST(menon::strchr(&s[0], 'd') == &s[3]);
    BOOST_TEST(menon::strchr(s, 'x') == nullptr);
  }
  { // wstring_view版
    constexpr auto s = L"abcdefg"sv;
    constexpr auto it = menon::strchr(s, L'd');
    BOOST_TEST(it == s.begin() + 3);
    BOOST_TEST(menon::strchr(s, L'x') == decltype(s.begin())());
  }
  { // wstring版
    auto s = L"abcdefg"s;
    auto it = menon::strchr(s, L'd');
    BOOST_TEST(it == s.begin() + 3);
    BOOST_TEST(menon::strchr(s, L'x') == decltype(s.begin())());
  }
}

// strrchr関数のテストコード
void test_strrchr()
{
  using namespace std::literals;

  { // char配列版
    constexpr auto s = "abcabcabc";
    constexpr auto it = menon::strrchr(s, 'b');
    BOOST_TEST_EQ(it, &s[7]);
    BOOST_TEST_EQ(menon::strrchr(&s[0], 'b'), &s[7]);
    BOOST_TEST_EQ(menon::strrchr(const_cast<char const*>(&s[0]), 'a'), &s[6]);
    BOOST_TEST_EQ(menon::strrchr(s, 'x'), nullptr);
  }
  { // string_view版
    constexpr auto s = "abcabcabc"sv;
    constexpr auto it = menon::strrchr(s, 'b');
    BOOST_TEST_EQ(it, s.begin() + 7);
    BOOST_TEST_EQ(menon::strrchr(s, 'x'), decltype(s.begin())());
  }
  { // string版
    auto s = "abcabcabc"s;
    auto it = menon::strrchr(s, 'a');
    BOOST_TEST(it == s.begin() + 6);
    BOOST_TEST(menon::strrchr(s, 'x') == decltype(s.begin())());
  }
}

int main()
{
  test_strchr();
  test_strrchr();
  return boost::report_errors();
}
