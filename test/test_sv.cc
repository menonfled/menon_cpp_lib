#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals::string_view_literals;
  using namespace std::literals::string_literals;
  char s[] = "abc";
  BOOST_TEST_EQ(menon::sv('a'), "a"sv);

  BOOST_TEST_EQ(menon::sv("abc", 2), "ab"sv);
  BOOST_TEST_EQ(menon::sv((char const*)nullptr, 2), ""sv);
  BOOST_TEST_EQ(menon::sv(s, 2), "ab"sv);

  BOOST_TEST_EQ(menon::sv("abc"), "abc"sv);
  BOOST_TEST_EQ(menon::sv((char const*)nullptr), ""sv);
  BOOST_TEST_EQ(menon::sv(s), "abc"sv);
  BOOST_TEST_EQ(menon::sv(""), ""sv);

  BOOST_TEST_EQ(menon::sv("abc"sv), "abc"sv);
  BOOST_TEST_EQ(menon::sv("abc"s), "abc"sv);
#if MENON_HAS_BOOST
  BOOST_TEST_EQ(menon::sv(boost::string_view("abc")), "abc"sv);
#endif
#if MENON_HAS_GSL
  BOOST_TEST_EQ(menon::sv(gsl::basic_string_span<char>(s, 3)), "abc"sv);
#endif

  {
    constexpr auto sv = "abcde"sv;
    constexpr auto a = menon::sv_to_array<3>("abcde"sv);
    BOOST_TEST_ALL_EQ(a.begin(), a.end(), sv.begin(), sv.begin() + 3);
  }
  return boost::report_errors();
}
