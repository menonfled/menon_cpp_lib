#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <vector>
#include <list>

void test_front()
{
  {
    std::vector<int> v;
    BOOST_TEST_EQ(menon::front(v), nullptr);
    v.push_back(1);
    BOOST_TEST_EQ(menon::front(v), v.data());
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    BOOST_TEST_EQ(menon::front(v), v.data());
  }
  {
    std::list<int> l;
    BOOST_TEST_EQ(menon::front(l), nullptr);
    l.push_back(1);
    BOOST_TEST_EQ(menon::front(l), &*l.begin());
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    BOOST_TEST_EQ(menon::front(l), &*l.begin());
  }
  {
    std::string s;
    BOOST_TEST_EQ(menon::front(s), nullptr);
    s.push_back('a');
    BOOST_TEST_EQ(menon::front(s), s.c_str());
    s.push_back('b');
    s.push_back('c');
    s.push_back('d');
    BOOST_TEST_EQ(menon::front(s), s.c_str());
  }
  {
    int a[10] {};
    BOOST_TEST_EQ(menon::front(a), &a[0]);
  }
}

void test_back()
{
  {
    std::vector<int> v;
    BOOST_TEST_EQ(menon::back(v), nullptr);
    v.push_back(1);
    BOOST_TEST_EQ(menon::back(v), v.data());
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    BOOST_TEST_EQ(menon::back(v), &*v.rbegin());
  }
  {
    std::list<int> l;
    BOOST_TEST_EQ(menon::back(l), nullptr);
    l.push_back(1);
    BOOST_TEST_EQ(menon::back(l), &*l.begin());
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    BOOST_TEST_EQ(menon::back(l), &*l.rbegin());
  }
  {
    std::string s;
    BOOST_TEST_EQ(menon::back(s), nullptr);
    s.push_back('a');
    BOOST_TEST_EQ(menon::back(s), s.c_str());
    s.push_back('b');
    s.push_back('c');
    s.push_back('d');
    BOOST_TEST_EQ(menon::back(s), &*s.rbegin());
  }
  {
    int a[10] {};
    BOOST_TEST_EQ(menon::front(a), &a[0]);
  }
}

int main()
{
  test_front();
  test_back();
  return boost::report_errors();
}