#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <initializer_list>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <array>
#include <span>

int main()
{
  {
    std::vector<int> v;
    BOOST_TEST(menon::has_reserve_v<decltype(v)>);
    BOOST_TEST(menon::has_clear_v<decltype(v)>);
    BOOST_TEST_NO_THROW(menon::reserve(v, 10));
    BOOST_TEST_EQ(v.capacity(), 10);
  }
  {
    std::list<int> l;
    BOOST_TEST(!menon::has_reserve_v<decltype(l)>);
    BOOST_TEST(menon::has_clear_v<decltype(l)>);
    BOOST_TEST_NO_THROW(menon::reserve(l, 10));
  }
  {
    std::set<int> s;
    BOOST_TEST(!menon::has_reserve_v<decltype(s)>);
    BOOST_TEST(menon::has_clear_v<decltype(s)>);
    BOOST_TEST_NO_THROW(menon::reserve(s, 10));
  }
  {
    std::array<int, 10> a;
    BOOST_TEST_NOT(menon::has_reserve<decltype(a)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(a, 10));
    BOOST_TEST_THROWS(menon::reserve(a, 11), std::out_of_range);
  }
  {
    int a[10];
    BOOST_TEST_NOT(menon::has_reserve<decltype(a)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(a, 10));
    BOOST_TEST_THROWS(menon::reserve(a, 11), std::out_of_range);
  }
  {
    std::initializer_list<int> il { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    BOOST_TEST_NOT(menon::has_reserve<decltype(il)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(il, 10));
    BOOST_TEST_THROWS(menon::reserve(il, 11), std::out_of_range);
  }
  {
    int a[10];
    std::span<int> s(a);
    BOOST_TEST_NOT(menon::has_reserve<decltype(s)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(s, 10));
    BOOST_TEST_THROWS(menon::reserve(s, 11), std::out_of_range);
  }
  return boost::report_errors();
}