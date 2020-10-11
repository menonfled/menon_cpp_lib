#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  BOOST_TEST_EQ(menon::ltrim("abcde", "ab"), "cde");
  BOOST_TEST_EQ(menon::ltrim(" \r\n\tabcde"), "abcde");
  BOOST_TEST_EQ(menon::ltrim("abcde", "xy"), "abcde");

  BOOST_TEST_EQ(menon::rtrim("abcde", "ed"), "abc");
  BOOST_TEST_EQ(menon::rtrim("abcde \r\n\t"), "abcde");
  BOOST_TEST_EQ(menon::rtrim("abcde", "xy"), "abcde");

  return boost::report_errors();
}
