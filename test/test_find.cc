// test_find.cc
#include "menon/algorithm.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>

// find関数のテストコード
void test_find()
{
  { // vectorに対する探索
    std::vector v = { 3, 2, 7, 1, 9, 5 };
    { // find
      auto p = menon::find(v, 7);
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
        BOOST_TEST_EQ(p, v.data() + 2);
      }
      p = menon::find(v, 6);
      BOOST_TEST_NOT(p);
    }
    { //cfing
      auto p = menon::cfind(v, 7);
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
        BOOST_TEST_EQ(p, v.data() + 2);
      }
      p = menon::cfind(v, 6);
      BOOST_TEST_NOT(p);
    }
  }
  { // dequeに対する探索
    std::deque d = { 3, 2, 7, 1, 9, 5 };
    auto p = menon::find(d, 7);
    BOOST_TEST(p);
    if (p)
    {
      BOOST_TEST_EQ(*p, 7);
    }
    p = menon::find(d, 6);
    BOOST_TEST_NOT(p);
  }
  { // listに対する探索
    std::list l = { 3, 2, 7, 1, 9, 5 };
    auto p = menon::find(l, 7);
    BOOST_TEST(p);
    if (p)
    {
      BOOST_TEST_EQ(*p, 7);
    }
    p = menon::find(l, 6);
    BOOST_TEST_NOT(p);
  }
  { // 配列に対する探索
    int a[] = { 3, 2, 7, 1, 9, 5 };
    { //find
      auto p = menon::find(a, 7);
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
        BOOST_TEST_EQ(p, a + 2);
      }
      p = menon::find(a, 6);
      BOOST_TEST_NOT(p);
    }
    { // cfind
      auto p = menon::cfind(a, 7);
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
        BOOST_TEST_EQ(p, a + 2);
      }
      p = menon::cfind(a, 6);
      BOOST_TEST_NOT(p);
    }
  }

  { // setに対する探索
    std::set s = { 3, 2, 7, 1, 9, 5 };
    { // finc
      auto p = menon::find(s, 7);
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
      }
      p = menon::find(s, 6);
      BOOST_TEST_NOT(p);
    }
    { // cfind
      auto p = menon::cfind(s, 7);
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
      }
      p = menon::cfind(s, 6);
      BOOST_TEST_NOT(p);
    }
  }

  { // mapに対する探索
    std::map<std::string, int> m = { { "d", 3 }, { "y", 2 }, { "c", 7 }, { "v", 1 } };
    { // find
      auto p = menon::find(m, "c");
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
      }
      p = menon::find(m, "k");
      BOOST_TEST_NOT(p);
    }
    { // cfind
      auto p = menon::cfind(m, "c");
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 7);
      }
      p = menon::cfind(m, "k");
      BOOST_TEST_NOT(p);
    }
  }
}

// find_if関数のテストコード
void test_find_if()
{
  { // vectorに対するfind_if
    std::vector v = { 3, 2, 7, 1, 9, 5 };
    {
      auto p = menon::find_if(v, [](auto value) {
        return value % 2 == 0;
      });
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 2);
        BOOST_TEST_EQ(p, v.data() + 1);
      }
      p = menon::find_if(v, [](auto value) {
        return value > 10;        
      });
      BOOST_TEST_NOT(p);
    }
  }

  { // vectorに対するcfind_if
    std::vector v = { 3, 2, 7, 1, 9, 5 };
    {
      auto p = menon::cfind_if(v, [](auto value) {
        return value % 2 == 0;
      });
      BOOST_TEST(p);
      if (p)
      {
        BOOST_TEST_EQ(*p, 2);
        BOOST_TEST_EQ(p, v.data() + 1);
      }
      p = menon::cfind_if(v, [](auto value) {
        return value > 10;        
      });
      BOOST_TEST_NOT(p);
    }
  }
}

int main()
{
  test_find();
  test_find_if();
  return boost::report_errors();
}
