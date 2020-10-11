#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  BOOST_TEST_EQ(menon::ltrim("abcde", "ab"), "cde");
  BOOST_TEST_EQ(menon::ltrim(" \r\n\tabcde"), "abcde");

  return boost::report_errors();
}
