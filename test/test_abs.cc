#include "menon/math.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  {
    constexpr auto x = menon::abs(-123);
    BOOST_TEST_EQ(x, 123);
    BOOST_TEST_EQ(menon::abs(std::numeric_limits<int>::max()), std::numeric_limits<int>::max());
    BOOST_TEST_THROWS(menon::abs(std::numeric_limits<int>::min()), std::out_of_range);
    static_assert(std::is_same_v<decltype(menon::abs((unsigned char)123)), int>);
    static_assert(std::is_same_v<decltype(menon::abs(123)), int>);
    static_assert(std::is_same_v<decltype(menon::abs(123U)), unsigned int>);
    static_assert(std::is_same_v<decltype(menon::abs(123L)), long>);
    static_assert(std::is_same_v<decltype(menon::abs(123LL)), long long>);
    BOOST_TEST_EQ(menon::abs(123L), 123L);
    BOOST_TEST_EQ(menon::abs(-1L), 1L);
    BOOST_TEST_EQ(menon::abs(std::numeric_limits<long>::max()), std::numeric_limits<long>::max());
    BOOST_TEST_THROWS(menon::abs(std::numeric_limits<long>::min()), std::out_of_range);
    BOOST_TEST_EQ(menon::abs(123LL), 123LL);
    BOOST_TEST_EQ(menon::abs(-1LL), 1LL);
    BOOST_TEST_EQ(menon::abs(std::numeric_limits<long long>::max()), std::numeric_limits<long long>::max());
    BOOST_TEST_THROWS(menon::abs(std::numeric_limits<long long>::min()), std::out_of_range);
  }
  return boost::report_errors();
}
