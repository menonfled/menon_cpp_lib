#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  std::string s = "abcdefghi";
  std::size_t n = s.size();

  constexpr auto r1 = menon::strlen("abcde");
  BOOST_TEST_EQ(r1, 5);
  constexpr auto r2 = menon::strlen("abcde", 3);
  BOOST_TEST_EQ(r2, 3);
  constexpr auto r3 = menon::strlen("abcde"sv);
  BOOST_TEST_EQ(r3, 5);

  BOOST_TEST_EQ(menon::strlen(s), n);
  BOOST_TEST_EQ(menon::strlen(s.c_str()), n);
  BOOST_TEST_EQ(menon::strlen(s.c_str(), s.size()), n);
  BOOST_TEST_EQ(menon::strlen(std::string_view(s)), n);

  return boost::report_errors();
}
