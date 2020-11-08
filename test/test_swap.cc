// test_swap.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

int main()
{
  { // int型のテストコード
    int a = 123;
    int b = 456;
    menon::swap(a, b);
    BOOST_TEST_EQ(a, 456);
    BOOST_TEST_EQ(b, 123);
  }
  { // double型のテストコード
    double a = 123;
    double b = 456;
    menon::swap(a, b);
    BOOST_TEST_EQ(a, 456);
    BOOST_TEST_EQ(b, 123);
  }
  { // 配列型のテストコード
    int a[] = { 1, 2, 3 };
    int b[] = { 4, 5, 6 };
    int x[] = { 1, 2, 3 };
    int y[] = { 4, 5, 6 };
    menon::swap(a, b);
    BOOST_TEST_ALL_EQ(std::begin(a), std::end(a), std::begin(y), std::end(y));
    BOOST_TEST_ALL_EQ(std::begin(b), std::end(b), std::begin(x), std::end(x));
  }
  { // string型のテストコード
    std::string a = "abc";
    std::string b = "def";
    menon::swap(a, b);
    BOOST_TEST_EQ(a, "def");
    BOOST_TEST_EQ(b, "abc");
  }
  { // vector型のテストコード
    std::vector a = { 1, 2, 3 };
    std::vector b = { 4, 5, 6 };
    auto x = a;
    auto y = b;
    menon::swap(a, b);
    BOOST_TEST_ALL_EQ(a.begin(), a.end(), y.begin(), y.end());
    BOOST_TEST_ALL_EQ(b.begin(), b.end(), x.begin(), x.end());
  }
  { // set型のテストコード
    std::set a = { 1, 2, 3 };
    std::set b = { 4, 5, 6 };
    auto x = a;
    auto y = b;
    menon::swap(a, b);
    BOOST_TEST_ALL_EQ(a.begin(), a.end(), y.begin(), y.end());
    BOOST_TEST_ALL_EQ(b.begin(), b.end(), x.begin(), x.end());
  }
  return boost::report_errors();
}