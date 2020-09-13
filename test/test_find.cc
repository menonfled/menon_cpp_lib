#include "menon/algorithm.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <deque>
#include <list>

int main()
{
  {
    std::vector v = { 3, 2, 7, 1, 9, 5 };
    {
      auto p = menon::find(v, 7);
      BOOST_TEST_NE(p, nullptr);
      if (p != nullptr)
      {
        BOOST_TEST_EQ(*p, 7);
        BOOST_TEST_EQ(p, v.data() + 2);
      }
      p = menon::find(v, 6);
      BOOST_TEST_EQ(p, nullptr);
    }
    {
      auto p = menon::cfind(v, 7);
      BOOST_TEST_NE(p, nullptr);
      if (p != nullptr)
      {
        BOOST_TEST_EQ(*p, 7);
        BOOST_TEST_EQ(p, v.data() + 2);
      }
      p = menon::cfind(v, 6);
      BOOST_TEST_EQ(p, nullptr);
    }
  }
  {
    std::deque d = { 3, 2, 7, 1, 9, 5 };
    auto p = menon::find(d, 7);
    BOOST_TEST_NE(p, nullptr);
    if (p != nullptr)
    {
      BOOST_TEST_EQ(*p, 7);
    }
    p = menon::find(d, 6);
    BOOST_TEST_EQ(p, nullptr);
  }
  {
    std::list l = { 3, 2, 7, 1, 9, 5 };
    auto p = menon::find(l, 7);
    BOOST_TEST_NE(p, nullptr);
    if (p != nullptr)
    {
      BOOST_TEST_EQ(*p, 7);
    }
    p = menon::find(l, 6);
    BOOST_TEST_EQ(p, nullptr);
  }
  return boost::report_errors();
}
