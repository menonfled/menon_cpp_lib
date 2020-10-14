#include "menon/math.hh"
#include <boost/core/lightweight_test.hpp>
#include <climits>

void test_div()
{
  {
    constexpr auto d = menon::div(12345, 67);
    BOOST_TEST_EQ(d.quot, 12345 / 67);
    BOOST_TEST_EQ(d.rem, 12345 % 67);
    BOOST_TEST_THROWS(menon::div(123, 0), std::invalid_argument);
    BOOST_TEST_THROWS(menon::div(INT_MIN, -1), std::out_of_range);
  }
  {
    constexpr auto d = menon::div(12345u, 67);
    BOOST_TEST_EQ(d.quot, 12345u / 67);
    BOOST_TEST_EQ(d.rem, 12345u % 67);
    BOOST_TEST_THROWS(menon::div(123u, 0), std::invalid_argument);
    BOOST_TEST_THROWS(menon::div(INT_MIN, -1u), std::out_of_range);
  }
  {
    constexpr auto d = menon::div(12345LL, 67);
    BOOST_TEST_EQ(d.quot, 12345LL / 67);
    BOOST_TEST_EQ(d.rem, 12345LL % 67);
    BOOST_TEST_THROWS(menon::div(123, 0LL), std::invalid_argument);
    BOOST_TEST_THROWS(menon::div(LONG_LONG_MIN, -1), std::out_of_range);
    BOOST_TEST_EQ(menon::div(INT_MIN, -1LL).quot, INT_MIN / -1LL);
  }
  {
    auto d = menon::div(12345.0, 67);
    BOOST_TEST_EQ(d.quot, 12345 / 67);
    BOOST_TEST_EQ(d.rem, 12345 % 67);
    BOOST_TEST_EQ(menon::div(12.345, 5.3).quot, 2);
    BOOST_TEST_EQ(menon::div(12.345, 5.3).rem, 12.345 - 5.3*2);
    BOOST_TEST_THROWS(menon::div(123.0, 0), std::invalid_argument);
    BOOST_TEST_EQ(menon::div(INT_MIN, -1.0).quot, INT_MIN * -1.0);
    BOOST_TEST(std::isnan(menon::div(INFINITY, INFINITY).quot));
    BOOST_TEST(std::isnan(menon::div(0.0, 0.0).quot));
  }
}

void test_udiv()
{
  {
    constexpr auto d = menon::udiv(12345u, 67u);
    BOOST_TEST_EQ(d.quot, 12345u / 67u);
    BOOST_TEST_EQ(d.rem, 12345u % 67u);
    BOOST_TEST_NOT(d.quot_sign);
    BOOST_TEST_NOT(d.rem_sign);
    BOOST_TEST_THROWS(menon::udiv(123u, 0u), std::invalid_argument);
  }
  {
    constexpr auto d = menon::udiv(12345ull, 67u);
    BOOST_TEST_EQ(d.quot, 12345ull / 67u);
    BOOST_TEST_EQ(d.rem, 12345ull % 67u);
    BOOST_TEST_NOT(d.quot_sign);
    BOOST_TEST_NOT(d.rem_sign);
    BOOST_TEST_THROWS(menon::udiv(123u, 0u), std::invalid_argument);
  }
}

int main()
{
  test_div();
  test_udiv();
  return boost::report_errors();
}
