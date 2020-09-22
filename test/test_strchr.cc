#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <cwchar>

int main()
{
  using namespace std::literals;

  {
    constexpr auto s = "abcdefg";
    constexpr auto it = menon::strchr(s, 'd');
    BOOST_TEST_EQ(it, &s[3]);
    BOOST_TEST_EQ(menon::strchr(&s[0], 'd'), &s[3]);
    BOOST_TEST_EQ(menon::strchr(const_cast<char const*>(&s[0]), 'd'), &s[3]);
    BOOST_TEST_EQ(menon::strchr(s, 'x'), nullptr);
  }
  {
    constexpr auto s = "abcdefg"sv;
    constexpr auto it = menon::strchr(s, 'd');
    BOOST_TEST_EQ(it, s.begin() + 3);
    BOOST_TEST_EQ(menon::strchr(s, 'x'), decltype(s.begin())());
  }
  {
    auto s = "abcdefg"s;
    auto it = menon::strchr(s, 'd');
    BOOST_TEST(it == s.begin() + 3);
    BOOST_TEST(menon::strchr(s, 'x') == decltype(s.begin())());
  }

  {
    constexpr auto s = L"abcdefg";
    constexpr auto it = menon::strchr(s, L'd');
    BOOST_TEST(it == &s[3]);
    BOOST_TEST(menon::strchr(&s[0], L'd') == &s[3]);
    BOOST_TEST(menon::strchr(s, L'x') == nullptr);
  }
  {
    constexpr auto s = L"abcdefg";
    constexpr auto it = menon::strchr(s, 'd');
    BOOST_TEST(it == &s[3]);
    BOOST_TEST(menon::strchr(&s[0], 'd') == &s[3]);
    BOOST_TEST(menon::strchr(s, 'x') == nullptr);
  }
  {
    constexpr auto s = L"abcdefg"sv;
    constexpr auto it = menon::strchr(s, L'd');
    BOOST_TEST(it == s.begin() + 3);
    BOOST_TEST(menon::strchr(s, L'x') == decltype(s.begin())());
  }
  {
    auto s = L"abcdefg"s;
    auto it = menon::strchr(s, L'd');
    BOOST_TEST(it == s.begin() + 3);
    BOOST_TEST(menon::strchr(s, L'x') == decltype(s.begin())());
  }

  return boost::report_errors();
}
