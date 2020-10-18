#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

// TODO まだテストケースが少ないので後ほど追加する。
int main()
{
  using namespace std::literals;

  {
    constexpr auto r = menon::clamp(5, 1, 10);
    BOOST_TEST_EQ(r, 5);
  }
  {
    constexpr auto r = menon::clamp(5, 6, 10);
    BOOST_TEST_EQ(r, 6);
  }
  {
    constexpr auto r = menon::clamp(5, 1, 4);
    BOOST_TEST_EQ(r, 4);
  }

  {
    constexpr auto r = menon::clamp(5, 1L, 10LL);
    BOOST_TEST_EQ(r, 5LL);
  }
  {
    constexpr auto r = menon::clamp(5U, 6UL, 10ULL);
    BOOST_TEST_EQ(r, 6ULL);
  }
  {
    constexpr auto r = menon::clamp(5.0, 1, 4.0);
    BOOST_TEST_EQ(r, 4);
  }
  {
    constexpr auto r = menon::clamp(5.0, 1.0, 4);
    BOOST_TEST_EQ(r, 4);
  }
  {
    constexpr auto r = menon::clamp(5.0, 1, 4);
    BOOST_TEST_EQ(r, 4);
  }

  return boost::report_errors();
}