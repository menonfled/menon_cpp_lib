﻿// test_div.cc
#include "menon/math.hh"
#include <boost/core/lightweight_test.hpp>
#include <climits>

// div関数のテストコード
void test_div()
{
  { // int型どうしの演算
    constexpr auto d = menon::div(12345, 67);
    BOOST_TEST_EQ(d.quot, 12345 / 67);
    BOOST_TEST_EQ(d.rem, 12345 % 67);
    BOOST_TEST_THROWS(menon::div(123, 0), std::invalid_argument);
    BOOST_TEST_THROWS(menon::div(INT_MIN, -1), std::out_of_range);
  }
  { // unsigned int型とint型の演算
    constexpr auto d = menon::div(12345u, 67);
    BOOST_TEST_EQ(d.quot, 12345u / 67);
    BOOST_TEST_EQ(d.rem, 12345u % 67);
    BOOST_TEST_THROWS(menon::div(123u, 0), std::invalid_argument);
    BOOST_TEST_THROWS(menon::div(INT_MIN, -1u), std::out_of_range);
  }
  { // long long型とint型の演算
    constexpr auto d = menon::div(12345LL, 67);
    BOOST_TEST_EQ(d.quot, 12345LL / 67);
    BOOST_TEST_EQ(d.rem, 12345LL % 67);
    BOOST_TEST_THROWS(menon::div(123, 0LL), std::invalid_argument);
    BOOST_TEST_THROWS(menon::div(LONG_LONG_MIN, -1), std::out_of_range);
    BOOST_TEST_EQ(menon::div(INT_MIN, -1LL).quot, INT_MIN / -1LL);
  }
  { // 浮動小数点型の演算
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

// udiv関数のテストコード
void test_udiv()
{
  { // unsigned int型どうしの演算
    constexpr auto d = menon::udiv(12345u, 67u);
    BOOST_TEST_EQ(d.quot, 12345u / 67u);
    BOOST_TEST_EQ(d.rem, 12345u % 67u);
    BOOST_TEST_NOT(d.quot_sign);
    BOOST_TEST_NOT(d.rem_sign);
    BOOST_TEST_THROWS(menon::udiv(123u, 0u), std::invalid_argument);
  }
  { // unsigned long long型とunsigned int型の演算
    constexpr auto d = menon::udiv(12345ull, 67u);
    BOOST_TEST_EQ(d.quot, 12345ull / 67u);
    BOOST_TEST_EQ(d.rem, 12345ull % 67u);
    BOOST_TEST_NOT(d.quot_sign);
    BOOST_TEST_NOT(d.rem_sign);
    BOOST_TEST_THROWS(menon::udiv(123u, 0u), std::invalid_argument);
  }
  { // int型どうしの演算
    constexpr auto d = menon::udiv(-12345, 67);
    BOOST_TEST_EQ(d.quot, 12345 / 67);
    BOOST_TEST_EQ(d.rem, 12345 % 67);
    BOOST_TEST(d.quot_sign);
    BOOST_TEST(d.rem_sign);
  }
  { // 浮動小数点型の演算
    auto d = menon::udiv(-12345.0, 67);
    BOOST_TEST_EQ(d.quot, 12345 / 67);
    BOOST_TEST_EQ(d.rem, 12345 % 67);
    BOOST_TEST(d.quot_sign);
    BOOST_TEST(d.rem_sign);
    BOOST_TEST_EQ(menon::udiv(12.345, 5.3).quot, 2);
    BOOST_TEST_EQ(menon::udiv(12.345, 5.3).rem, 12.345 - 5.3*2);
    BOOST_TEST_THROWS(menon::udiv(123.0, 0), std::invalid_argument);
    BOOST_TEST_EQ(menon::udiv(INT_MIN, -1.0).quot, -(double)INT_MIN);
    BOOST_TEST(std::isnan(menon::udiv(INFINITY, INFINITY).quot));
    BOOST_TEST(std::isnan(menon::udiv(0.0, 0.0).quot));
  }
}

int main()
{
  test_div();
  test_udiv();
  return boost::report_errors();
}
