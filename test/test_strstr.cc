// test_strstr.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cwchar>

// strstr関数のテストコード
void test_strstr()
{
  using namespace std::literals;

  { // char配列版
    constexpr auto s1 = "aaaaabbbcc";
    constexpr auto s2 = "ab";
    constexpr auto r = menon::strstr(s1, s2);
    BOOST_TEST_EQ(r, std::strstr(s1, s2));
    BOOST_TEST_EQ(menon::strstr((char*)nullptr, s2), nullptr);
    BOOST_TEST_EQ(menon::strstr(s1, (char*)nullptr), s1);
  }
  { // string_viewおよびchar配列版
    constexpr auto s = "aaaaabbbcc";
    constexpr auto s1 = "aaaaabbbcc"sv;
    constexpr auto s2 = "ab";
    constexpr auto r = menon::strstr(s1, s2);
    BOOST_TEST_EQ(r - s1.begin(), std::strstr(s, s2) - s);
  }
  { // string_view版
    constexpr auto s = "aaaaabbbcc";
    constexpr auto s1 = "aaaaabbbcc"sv;
    constexpr auto s2 = "ab"sv;
    constexpr auto r = menon::strstr(s1, s2);
    BOOST_TEST_EQ(r - s1.begin(), std::strstr(s, "ab") - s);
  }
  { // stringおよびchar配列版
    constexpr auto s = "aaaaabbbcc";
    auto s1 = "aaaaabbbcc"s;
    constexpr auto s2 = "ab";
    auto r = menon::strstr(s1, s2);
    BOOST_TEST_EQ(r - s1.begin(), std::strstr(s, s2) - s);
  }

  { // wchar_t配列版
    constexpr auto s1 = L"aaaaabbbcc";
    constexpr auto s2 = L"ab";
    constexpr auto r = menon::strstr(s1, s2);
    BOOST_TEST(r == std::wcsstr(s1, s2));
    BOOST_TEST(menon::strstr((wchar_t*)nullptr, s2) == nullptr);
    BOOST_TEST(menon::strstr(s1, (wchar_t*)nullptr) == s1);
  }
}

int main()
{
  test_strstr();

  return boost::report_errors();
}
