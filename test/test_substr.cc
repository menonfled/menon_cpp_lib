#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  constexpr auto s = "abcdef";
  constexpr auto wcs = L"abcdef";
  auto str = "abcdef"s;
  auto wstr = L"abcdef"s;

  constexpr auto t = menon::substr(s, 2, 3);  
  BOOST_TEST_EQ(t, "cde");
  BOOST_TEST_EQ(menon::substr(s, 2, 10), "cdef");
  BOOST_TEST_THROWS(menon::substr(s, 10, 3), std::out_of_range);

  BOOST_TEST(menon::substr(wcs, 2, 3) == L"cde");
  BOOST_TEST(menon::substr(wcs, 2, 10) == L"cdef");
  BOOST_TEST_THROWS(menon::substr(s, 10, 3), std::out_of_range);

  BOOST_TEST_EQ(menon::substr(str, 2, 3), "cde");
  BOOST_TEST_EQ(menon::substr(str, 2, 10), "cdef");
  BOOST_TEST_THROWS(menon::substr(str, 10, 3), std::out_of_range);

  BOOST_TEST(menon::substr(wstr, 2, 3) == L"cde");
  BOOST_TEST(menon::substr(wstr, 2, 10) == L"cdef");
  BOOST_TEST_THROWS(menon::substr(wstr, 10, 3), std::out_of_range);

  return boost::report_errors();
}