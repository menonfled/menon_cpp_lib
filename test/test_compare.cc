#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

int main()
{
  using namespace std::literals;

  BOOST_TEST(menon::lt(1, 2));
  BOOST_TEST(!menon::lt(2, 1));
  BOOST_TEST(!menon::lt(2, 2));
  BOOST_TEST(menon::lt(1L, 2));
  BOOST_TEST(!menon::lt(2, 1L));
  BOOST_TEST(!menon::lt(2, 2LL));
  BOOST_TEST(menon::lt(-2, 1));
  BOOST_TEST(menon::lt(-2, 1u));
  BOOST_TEST(menon::lt(123.45, 345.67));
  return boost::report_errors();
}