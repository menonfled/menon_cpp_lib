// test_abc.cc
#include "menon/math.hh"
#include <boost/core/lightweight_test.hpp>

// abs関数のテストコード
void test_abs()
{
  // int型のテスト
  constexpr auto x = menon::abs(-123);
  BOOST_TEST_EQ(x, 123);
  BOOST_TEST_EQ(menon::abs(std::numeric_limits<int>::max()), std::numeric_limits<int>::max());
  BOOST_TEST_THROWS(menon::abs(std::numeric_limits<int>::min()), std::out_of_range);

  // 返却値の型のテスト
  static_assert(std::is_same_v<decltype(menon::abs((unsigned char)123)), int>);
  static_assert(std::is_same_v<decltype(menon::abs(123)), int>);
  static_assert(std::is_same_v<decltype(menon::abs(123U)), unsigned int>);
  static_assert(std::is_same_v<decltype(menon::abs(123L)), long>);
  static_assert(std::is_same_v<decltype(menon::abs(123LL)), long long>);

  // long型のテスト
  BOOST_TEST_EQ(menon::abs(123L), 123L);
  BOOST_TEST_EQ(menon::abs(-1L), 1L);
  BOOST_TEST_EQ(menon::abs(std::numeric_limits<long>::max()), std::numeric_limits<long>::max());
  BOOST_TEST_THROWS(menon::abs(std::numeric_limits<long>::min()), std::out_of_range);

  // long long型のテスト
  BOOST_TEST_EQ(menon::abs(123LL), 123LL);
  BOOST_TEST_EQ(menon::abs(-1LL), 1LL);
  BOOST_TEST_EQ(menon::abs(std::numeric_limits<long long>::max()), std::numeric_limits<long long>::max());
  BOOST_TEST_THROWS(menon::abs(std::numeric_limits<long long>::min()), std::out_of_range);

  // 浮動小数点数のテスト
  BOOST_TEST_EQ(menon::abs(1.23), 1.23);
  BOOST_TEST_EQ(menon::abs(-1.0), 1.0);
  BOOST_TEST_EQ(menon::abs(std::numeric_limits<long long>::max()), std::numeric_limits<long long>::max());
  BOOST_TEST_THROWS(menon::abs(std::numeric_limits<long long>::min()), std::out_of_range);
}

// uabs関数のテストコード
void test_uabs()
{
  // int型およびunsigned int型のテスト
  constexpr auto x1 = menon::uabs(-123);
  BOOST_TEST_EQ(x1, 123u);
  constexpr auto y1 = menon::uabs(123);
  BOOST_TEST_EQ(y1, 123u);
  static_assert(std::is_same_v<decltype(menon::uabs(-123)), unsigned int>);
  BOOST_TEST_EQ(menon::uabs(std::numeric_limits<int>::min()), std::numeric_limits<int>::max() + 1u);

  // long型およびunsigned long型のテスト
  constexpr auto x2 = menon::uabs(-123L);
  BOOST_TEST_EQ(x2, 123UL);
  constexpr auto y2 = menon::uabs(123L);
  BOOST_TEST_EQ(y2, 123UL);
  static_assert(std::is_same_v<decltype(menon::uabs(-123L)), unsigned long>);
  BOOST_TEST_EQ(menon::uabs(std::numeric_limits<long>::min()), std::numeric_limits<long>::max() + 1UL);

  // long long型およびunsigned long long型のテスト
  constexpr auto x3 = menon::uabs(-123LL);
  BOOST_TEST_EQ(x3, 123ULL);
  constexpr auto y3 = menon::uabs(123LL);
  BOOST_TEST_EQ(y3, 123ULL);
  static_assert(std::is_same_v<decltype(menon::uabs(-123LL)), unsigned long long>);
  BOOST_TEST_EQ(menon::uabs(std::numeric_limits<long>::min()), std::numeric_limits<long>::max() + 1ULL);

  // 浮動小数点数のテスト
  constexpr auto x = menon::uabs(-1.23);
  BOOST_TEST_EQ(x, 1.23);
  constexpr auto y = menon::uabs(1.23);
  BOOST_TEST_EQ(y, 1.23);
  static_assert(std::is_same_v<decltype(menon::uabs(-1.23)), double>);
  BOOST_TEST_EQ(menon::uabs(-std::numeric_limits<double>::max()), std::numeric_limits<double>::max());
}

int main()
{
  test_abs();
  test_uabs();
  return boost::report_errors();
}
