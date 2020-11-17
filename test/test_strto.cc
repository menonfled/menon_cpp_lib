// test_strto.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstdlib>

void test_strto()
{
  using namespace std::literals;

  // int型版
  std::size_t endpos;
  BOOST_TEST_EQ(menon::strto<int>("12345", &endpos), 12345);
  BOOST_TEST_EQ(endpos, 5);
  BOOST_TEST_EQ(menon::strto<int>("012345", &endpos), 012345);
  BOOST_TEST_EQ(endpos, 6);
  BOOST_TEST_EQ(menon::strto<int>("0x12345", &endpos), 0x12345);
  BOOST_TEST_EQ(endpos, 7);
  BOOST_TEST_EQ(menon::strto<int>("abcdx", &endpos, 16), 0xabcd);
  BOOST_TEST_EQ(endpos, 4);
  BOOST_TEST_EQ(menon::strto<long>("abcd", &endpos, 36), std::strtol("abcd", nullptr, 36));
  BOOST_TEST_EQ(endpos, 4);
  BOOST_TEST_THROWS(menon::strto<int>("999999999999999999999", &endpos), std::overflow_error);

  // unsigned int型版
  BOOST_TEST_EQ(menon::strto<unsigned int>("12345", &endpos), 12345u);
  BOOST_TEST_EQ(menon::strto<unsigned int>("ffffffff", &endpos, 16), 0xffffffff);
  BOOST_TEST_THROWS(menon::strto<unsigned int>("100000000", &endpos, 16), std::overflow_error);
}

void test_strtox()
{
  // strtol関数のテストコード
  char const* s_abcd = "abcd";
  char const* endptr;
  BOOST_TEST_EQ(menon::strtol(s_abcd, &endptr, 36), std::strtol(s_abcd, nullptr, 36));
  BOOST_TEST_EQ(endptr, s_abcd + std::strlen(s_abcd));
  BOOST_TEST_THROWS(menon::strtol("999999999999999999999", &endptr), std::overflow_error);

  // strtoul関数のテストコード
  BOOST_TEST_EQ(menon::strtoul(s_abcd, &endptr, 36), std::strtoul(s_abcd, nullptr, 36));
  BOOST_TEST_EQ(endptr, s_abcd + std::strlen(s_abcd));
  BOOST_TEST_THROWS(menon::strtoul("9999999999999999999999", &endptr), std::overflow_error);

  // strtoll関数のテストコード
  BOOST_TEST_EQ(menon::strtoll(s_abcd, &endptr, 36), std::strtol(s_abcd, nullptr, 36));
  BOOST_TEST_EQ(endptr, s_abcd + std::strlen(s_abcd));
  BOOST_TEST_THROWS(menon::strtoll("999999999999999999999999999999999999999999", &endptr), std::overflow_error);

  // strtoull関数のテストコード
  BOOST_TEST_EQ(menon::strtoull(s_abcd, &endptr, 36), std::strtoull(s_abcd, nullptr, 36));
  BOOST_TEST_EQ(endptr, s_abcd + std::strlen(s_abcd));
  BOOST_TEST_THROWS(menon::strtoull("9999999999999999999999999999999999999999999", &endptr), std::overflow_error);
}

int main()
{
  test_strto();
  test_strtox();
  return boost::report_errors();
}