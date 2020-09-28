#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstdlib>

int main()
{
  using namespace std::literals;

  {
    std::size_t endpos;
    BOOST_TEST_EQ(menon::strto<int>("12345", &endpos), 12345);
    BOOST_TEST_EQ(endpos, 5);
    BOOST_TEST_EQ(menon::strto<int>("012345", &endpos), 012345);
    BOOST_TEST_EQ(endpos, 6);
    BOOST_TEST_EQ(menon::strto<int>("0x12345", &endpos), 0x12345);
    BOOST_TEST_EQ(endpos, 7);
    BOOST_TEST_EQ(menon::strto<int>("abcd", &endpos, 16), 0xabcd);
    BOOST_TEST_EQ(endpos, 4);
    BOOST_TEST_EQ(menon::strto<long>("abcd", &endpos, 36), std::strtol("abcd", nullptr, 36));
    BOOST_TEST_EQ(endpos, 4);
    BOOST_TEST_THROWS(menon::strto<int>("999999999999999999999", &endpos), std::overflow_error);
  }
  return boost::report_errors();
}