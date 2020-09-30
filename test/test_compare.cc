#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  BOOST_TEST(menon::lt(1, 2));
  BOOST_TEST(!menon::lt(2, 1));
  BOOST_TEST(!menon::lt(2, 2));
  BOOST_TEST(menon::lt(1L, 2));
  BOOST_TEST(!menon::lt(2, 1L));
  BOOST_TEST(!menon::lt(2, 2LL));
  BOOST_TEST(menon::lt(-2, 1));
  BOOST_TEST(menon::lt(-2, 1u));
  BOOST_TEST(menon::lt(123.45, 345.67));
  BOOST_TEST(!menon::lt(123.45, 123.45));
  return boost::report_errors();
}