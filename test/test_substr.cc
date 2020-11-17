// test_substr.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

using namespace std::literals;

constexpr auto s = "abcdef";
constexpr auto wcs = L"abcdef";
auto str = "abcdef"s;
auto wstr = L"abcdef"s;

void test_substr()
{
  // char配列版
  constexpr auto t = menon::substr(s, 2, 3);  
  BOOST_TEST_EQ(t, "cde");
  BOOST_TEST_EQ(menon::substr(s, 2, 10), "cdef");
  BOOST_TEST_THROWS(menon::substr(s, 10, 3), std::out_of_range);

  // wchar_t配列版
  BOOST_TEST(menon::substr(wcs, 2, 3) == L"cde");
  BOOST_TEST(menon::substr(wcs, 2, 10) == L"cdef");
  BOOST_TEST_THROWS(menon::substr(s, 10, 3), std::out_of_range);

  // string版
  BOOST_TEST_EQ(menon::substr(str, 2, 3), "cde");
  BOOST_TEST_EQ(menon::substr(str, 2, 10), "cdef");
  BOOST_TEST_THROWS(menon::substr(str, 10, 3), std::out_of_range);

  // wstring版
  BOOST_TEST(menon::substr(wstr, 2, 3) == L"cde");
  BOOST_TEST(menon::substr(wstr, 2, 10) == L"cdef");
  BOOST_TEST_THROWS(menon::substr(wstr, 10, 3), std::out_of_range);
}

void test_left()
{
  constexpr auto t = menon::left(s, 3);  
  BOOST_TEST_EQ(t, "abc");
  BOOST_TEST_EQ(menon::left(s, 10), s);

  BOOST_TEST(menon::left(wcs, 3) == L"abc");
  BOOST_TEST(menon::left(wcs, 10) == wcs);
}

void test_right()
{
  constexpr auto t = menon::right(s, 3);  
  BOOST_TEST_EQ(t, "def");
  BOOST_TEST_EQ(menon::right(s, 10), s);

  BOOST_TEST(menon::right(wcs, 3) == L"def");
  BOOST_TEST(menon::right(wcs, 10) == wcs);
}

int main()
{
  test_substr();
  test_left();
  test_right();
  return boost::report_errors();
}