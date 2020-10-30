// test_compare.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>

// lt関数のテストコード
void test_lt()
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
}

// gt関数のテストコード
void test_gt()
{
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
}

// le関数のテストコード
void test_le()
{
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
}

// ge関数のテストコード
void test_ge()
{
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
}

// eq関数のテストコード
void test_eq()
{
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
}

// ne関数のテストコード
void test_ne()
{
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
}

int main()
{
  test_lt();
  test_gt();
  test_le();
  test_ge();
  test_eq();
  test_ne();
  return boost::report_errors();
}