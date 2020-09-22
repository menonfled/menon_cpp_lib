#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  {
    constexpr auto s1 = "aaaaabbbcc";
    constexpr auto s2 = "ab";
    constexpr auto r = menon::strspn(s1, s2);
    BOOST_TEST_EQ(r, std::strspn(s1, s2));
  }
  {
    constexpr auto s1 = "aaaaabbbcc"sv;
    constexpr auto s2 = "ab"sv;
    constexpr auto r = menon::strspn(s1, s2);
    BOOST_TEST_EQ(r, std::strspn("aaaaabbbcc", "ab"));
  }
  {
    auto s1 = "aaaaabbbcc"s;
    auto s2 = "ab";
    auto r = menon::strspn(s1, s2);
    BOOST_TEST_EQ(r, std::strspn(s1.c_str(), s2));
  }
  {
    constexpr auto s1 = "aaaaabbbcc";
    auto s2 = "ab"s;
    auto r = menon::strspn(s1, s2);
    BOOST_TEST_EQ(r, std::strspn(s1, s2.c_str()));
  }

  return boost::report_errors();
}
