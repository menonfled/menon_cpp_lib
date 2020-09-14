#include "menon/algorithm.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>

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
  int a[] = { 3, 2, 7, 1, 9, 5 };
  {
    auto p = menon::find(a, 7);
    BOOST_TEST_NE(p, nullptr);
    if (p != nullptr)
    {
      BOOST_TEST_EQ(*p, 7);
      BOOST_TEST_EQ(p, a + 2);
    }
    p = menon::find(a, 6);
    BOOST_TEST_EQ(p, nullptr);
  }
  {
    auto p = menon::cfind(a, 7);
    BOOST_TEST_NE(p, nullptr);
    if (p != nullptr)
    {
      BOOST_TEST_EQ(*p, 7);
      BOOST_TEST_EQ(p, a + 2);
    }
    p = menon::cfind(a, 6);
    BOOST_TEST_EQ(p, nullptr);
  }

  {
    std::set s = { 3, 2, 7, 1, 9, 5 };
    {
      auto p = menon::find(s, 7);
      BOOST_TEST_NE(p, nullptr);
      if (p != nullptr)
      {
        BOOST_TEST_EQ(*p, 7);
      }
      p = menon::find(s, 6);
      BOOST_TEST_EQ(p, nullptr);
    }
    {
      auto p = menon::cfind(s, 7);
      BOOST_TEST_NE(p, nullptr);
      if (p != nullptr)
      {
        BOOST_TEST_EQ(*p, 7);
      }
      p = menon::cfind(s, 6);
      BOOST_TEST_EQ(p, nullptr);
    }
  }

  std::map<std::string, int> m = { { "d", 3 }, { "y", 2 }, { "c", 7 }, { "v", 1 } };
  {
    auto p = menon::find(m, "c");
    BOOST_TEST_NE(p, nullptr);
    if (p != nullptr)
    {
      BOOST_TEST_EQ(*p, 7);
    }
    p = menon::find(m, "k");
    BOOST_TEST_EQ(p, nullptr);
  }
  {
    auto p = menon::cfind(m, "c");
    BOOST_TEST_NE(p, nullptr);
    if (p != nullptr)
    {
      BOOST_TEST_EQ(*p, 7);
    }
    p = menon::cfind(m, "k");
    BOOST_TEST_EQ(p, nullptr);
  }
  return boost::report_errors();
}
