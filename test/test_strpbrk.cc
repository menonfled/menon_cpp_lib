// test_strpbrk.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

// strpbrk関数のテストコード
void test_strpbrk()
{
  using namespace std::literals;

  { // char配列版
    constexpr auto s1 = "aaaaabbbcc";
    constexpr auto s2 = "ab";
    constexpr auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk(s1, s2));
  }
  { // string_view版
    constexpr auto s1 = "aaaaabbbcc"sv;
    constexpr auto s2 = "ab"sv;
    constexpr auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk("aaaaabbbcc", "ab"));
  }
  { // stringおよびchar配列版
    auto s1 = "aaaaabbbcc"s;
    auto s2 = "ab";
    auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk(s1.c_str(), s2));
  }
  { // char配列およびstring版
    constexpr auto s1 = "aaaaabbbcc";
    auto s2 = "ab"s;
    auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk(s1, s2.c_str()));
  }
}

int main()
{
  test_strpbrk();

  return boost::report_errors();
}
