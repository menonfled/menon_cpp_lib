// test_trim.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

using namespace std::literals;

void test_ltrim()
{
  BOOST_TEST_EQ(menon::ltrim("abcde", "ab"), "cde");
  BOOST_TEST_EQ(menon::ltrim(" \r\n\tabcde"), "abcde");
  BOOST_TEST_EQ(menon::ltrim("abcde", "xy"), "abcde");
}

void test_rtrim()
{
  BOOST_TEST_EQ(menon::rtrim("abcde", "ed"), "abc");
  BOOST_TEST_EQ(menon::rtrim("abcde \r\n\t"), "abcde");
  BOOST_TEST_EQ(menon::rtrim("abcde", "xy"), "abcde");
}

void test_trim()
{
  BOOST_TEST_EQ(menon::trim("abcde", "ab"), "cde");
  BOOST_TEST_EQ(menon::trim(" \r\n\tabcde"), "abcde");
  BOOST_TEST_EQ(menon::trim("abcde", "xy"), "abcde");
  BOOST_TEST_EQ(menon::trim("abcde", "ed"), "abc");
  BOOST_TEST_EQ(menon::trim("abcde \r\n\t"), "abcde");
  BOOST_TEST_EQ(menon::trim("abcde", "xy"), "abcde");
  BOOST_TEST_EQ(menon::trim("abcde", "eda"), "bc");
  BOOST_TEST_EQ(menon::trim(" \r\n\tabcde \r\n\t"), "abcde");
}

int main()
{
  test_ltrim();
  test_rtrim();
  test_trim();
  return boost::report_errors();
}
