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

  BOOST_TEST(!menon::gt(1, 2));
  BOOST_TEST(menon::gt(2, 1));
  BOOST_TEST(!menon::gt(2, 2));
  BOOST_TEST(!menon::gt(1L, 2));
  BOOST_TEST(menon::gt(2, 1L));
  BOOST_TEST(!menon::gt(2, 2LL));
  BOOST_TEST(menon::gt(2, -1));
  BOOST_TEST(!menon::gt(-2, 1));
  BOOST_TEST(!menon::gt(-2, 1u));
  BOOST_TEST(!menon::gt(123.45, 345.67));
  BOOST_TEST(!menon::gt(123.45, 123.45));

  BOOST_TEST(menon::le(1, 2));
  BOOST_TEST(!menon::le(2, 1));
  BOOST_TEST(menon::le(2, 2));
  BOOST_TEST(menon::le(1L, 2));
  BOOST_TEST(!menon::le(2, 1L));
  BOOST_TEST(menon::le(2, 2LL));
  BOOST_TEST(menon::le(-2, 1));
  BOOST_TEST(menon::le(-2, 1u));
  BOOST_TEST(menon::le(123.45, 345.67));
  BOOST_TEST(menon::le(123.45, 123.45));

  BOOST_TEST(!menon::ge(1, 2));
  BOOST_TEST(menon::ge(2, 1));
  BOOST_TEST(menon::ge(2, 2));
  BOOST_TEST(!menon::ge(1L, 2));
  BOOST_TEST(menon::ge(2, 1L));
  BOOST_TEST(menon::ge(2, 2LL));
  BOOST_TEST(!menon::ge(-2, 1));
  BOOST_TEST(!menon::ge(-2, 1u));
  BOOST_TEST(!menon::ge(123.45, 345.67));
  BOOST_TEST(menon::ge(123.45, 123.45));

  BOOST_TEST(!menon::eq(1, 2));
  BOOST_TEST(!menon::eq(2, 1));
  BOOST_TEST(menon::eq(2, 2));
  BOOST_TEST(!menon::eq(1L, 2));
  BOOST_TEST(!menon::eq(2, 1L));
  BOOST_TEST(menon::eq(2, 2LL));
  BOOST_TEST(!menon::eq(-2, 1));
  BOOST_TEST(!menon::eq(-2, 1u));
  BOOST_TEST(!menon::eq(123.45, 345.67));
  BOOST_TEST(menon::eq(123.45, 123.45));

  BOOST_TEST(menon::ne(1, 2));
  BOOST_TEST(menon::ne(2, 1));
  BOOST_TEST(!menon::ne(2, 2));
  BOOST_TEST(menon::ne(1L, 2));
  BOOST_TEST(menon::ne(2, 1L));
  BOOST_TEST(!menon::ne(2, 2LL));
  BOOST_TEST(menon::ne(-2, 1));
  BOOST_TEST(menon::ne(-2, 1u));
  BOOST_TEST(menon::ne(-1, ~0u));
  BOOST_TEST(menon::ne(123.45, 345.67));
  BOOST_TEST(!menon::ne(123.45, 123.45));

  return boost::report_errors();
}