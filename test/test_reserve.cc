// test_reserve.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <set>
#include <array>
#include <span>

int main()
{
  { // string用のテストコード
    std::string s;
    BOOST_TEST(menon::has_reserve_v<decltype(s)>);
    BOOST_TEST(menon::has_clear_v<decltype(s)>);
    BOOST_TEST_NO_THROW(menon::reserve(s, 10));
    BOOST_TEST_GE(s.capacity(), 10);
  }
  { // string_view用のテストコード
    std::string_view sv("1234567890");
    BOOST_TEST(!menon::has_reserve_v<decltype(sv)>);
    BOOST_TEST(!menon::has_clear_v<decltype(sv)>);
    BOOST_TEST_NO_THROW(menon::reserve(sv, 10));
    BOOST_TEST_THROWS(menon::reserve(sv, 11), std::out_of_range);
  }
  { // vector用のテストコード
    std::vector<int> v;
    BOOST_TEST(menon::has_reserve_v<decltype(v)>);
    BOOST_TEST(menon::has_clear_v<decltype(v)>);
    BOOST_TEST_NO_THROW(menon::reserve(v, 10));
    BOOST_TEST_GE(v.capacity(), 10);
  }
  { // list用のテストコード
    std::list<int> l;
    BOOST_TEST(!menon::has_reserve_v<decltype(l)>);
    BOOST_TEST(menon::has_clear_v<decltype(l)>);
    BOOST_TEST_NO_THROW(menon::reserve(l, 10));
  }
  { // set用のテストコード
    std::set<int> s;
    BOOST_TEST(!menon::has_reserve_v<decltype(s)>);
    BOOST_TEST(menon::has_clear_v<decltype(s)>);
    BOOST_TEST_NO_THROW(menon::reserve(s, 10));
  }
  { // array用のテストコード
    std::array<int, 10> a;
    BOOST_TEST_NOT(menon::has_reserve<decltype(a)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(a, 10));
    BOOST_TEST_THROWS(menon::reserve(a, 11), std::out_of_range);
  }
  { // 配列用のテストコード
    int a[10];
    BOOST_TEST_NOT(menon::has_reserve<decltype(a)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(a, 10));
    BOOST_TEST_THROWS(menon::reserve(a, 11), std::out_of_range);
  }
  { // initializer_list用のテストコード
    std::initializer_list<int> il { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    BOOST_TEST_NOT(menon::has_reserve<decltype(il)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(il, 10));
    BOOST_TEST_THROWS(menon::reserve(il, 11), std::out_of_range);
  }
  { // span用のテストコード
    int a[10];
    std::span<int> s(a);
    BOOST_TEST_NOT(menon::has_reserve<decltype(s)>::value);
    BOOST_TEST_NO_THROW(menon::reserve(s, 10));
    BOOST_TEST_THROWS(menon::reserve(s, 11), std::out_of_range);
  }
  return boost::report_errors();
}