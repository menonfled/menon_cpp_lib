#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

int main()
{
  using namespace std::literals;

  BOOST_TEST(menon::lt(1, 2));
  BOOST_TEST(menon::lt(-2, 1));
  BOOST_TEST(menon::lt(123.45, 345.67));
  BOOST_TEST(menon::lt("abc", "def"));
  BOOST_TEST(menon::lt("abc"s, "def"s));
  BOOST_TEST(menon::lt("abc"sv, "def"sv));
  // BOOST_TEST(menon::lt("abc"s, "def"));
  // BOOST_TEST(menon::lt("abc", "def"s));
  // BOOST_TEST(menon::lt("abc"sv, "def"));
  return boost::report_errors();
}