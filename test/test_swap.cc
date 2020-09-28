#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

int main()
{
  {
    int a = 123;
    int b = 456;
    menon::swap(a, b);
    BOOST_TEST_EQ(a, 456);
    BOOST_TEST_EQ(b, 123);
  }
  {
    double a = 123;
    double b = 456;
    menon::swap(a, b);
    BOOST_TEST_EQ(a, 456);
    BOOST_TEST_EQ(b, 123);
  }
  {
    std::string a = "abc";
    std::string b = "def";
    menon::swap(a, b);
    BOOST_TEST_EQ(a, "def");
    BOOST_TEST_EQ(b, "abc");
  }
  {
    std::vector a = { 1, 2, 3 };
    std::vector b = { 4, 5, 6 };
    auto x = a;
    auto y = b;
    menon::swap(a, b);
    BOOST_TEST_ALL_EQ(a.begin(), a.end(), y.begin(), y.end());
    BOOST_TEST_ALL_EQ(b.begin(), b.end(), x.begin(), x.end());
  }
  {
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