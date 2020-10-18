#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

int main()
{
  using namespace std::literals;
  {
    constexpr auto r = menon::max(1, 2);
    BOOST_TEST_EQ(r, 2);
  }
  {
    constexpr auto r = menon::max(1, 2L);
    BOOST_TEST_EQ(r, 2L);
  }
  {
    constexpr double x = 1.23;
    constexpr double y = 2.34f;
    constexpr auto r = menon::max(x, y);
    BOOST_TEST_EQ(r, y);
  }
  {
    constexpr auto r = menon::max("abc"sv, "def"sv);
    BOOST_TEST_EQ(r, "def"sv);
  }
  {
    constexpr auto r = menon::max(1, 2, 3);
    BOOST_TEST_EQ(r, 3);
  }

  {
    constexpr auto r = menon::min(1, 2);
    BOOST_TEST_EQ(r, 1);
  }
  {
    constexpr auto r = menon::min(1, 2L);
    BOOST_TEST_EQ(r, 1L);
  }
  {
    constexpr double x = 1.23;
    constexpr double y = 2.34f;
    constexpr auto r = menon::min(x, y);
    BOOST_TEST_EQ(r, x);
  }
  {
    constexpr auto r = menon::min("abc"sv, "def"sv);
    BOOST_TEST_EQ(r, "abc"sv);
  }
  {
    constexpr auto r = menon::min(1, 2, 3);
    BOOST_TEST_EQ(r, 1);
  }
  return boost::report_errors();
}