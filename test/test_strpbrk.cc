#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

void test_strpbrk()
{
  using namespace std::literals;

  {
    constexpr auto s1 = "aaaaabbbcc";
    constexpr auto s2 = "ab";
    constexpr auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk(s1, s2));
  }
  {
    constexpr auto s1 = "aaaaabbbcc"sv;
    constexpr auto s2 = "ab"sv;
    constexpr auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk("aaaaabbbcc", "ab"));
  }
  {
    auto s1 = "aaaaabbbcc"s;
    auto s2 = "ab";
    auto r = menon::strpbrk(s1, s2);
    BOOST_TEST(r == std::strpbrk(s1.c_str(), s2));
  }
  {
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
