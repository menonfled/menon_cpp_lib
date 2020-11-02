// test_front.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <vector>
#include <list>

// front関数のテストコード
void test_front()
{
  { // vectorの場合
    std::vector<int> v;
    BOOST_TEST_EQ(menon::front(v), nullptr);
    v.push_back(1);
    BOOST_TEST_EQ(menon::front(v), v.data());
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    BOOST_TEST_EQ(menon::front(v), v.data());
  }
  { // listの場合
    std::list<int> l;
    BOOST_TEST_EQ(menon::front(l), nullptr);
    l.push_back(1);
    BOOST_TEST_EQ(menon::front(l), &*l.begin());
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    BOOST_TEST_EQ(menon::front(l), &*l.begin());
  }
  { // stringの場合
    std::string s;
    BOOST_TEST_EQ(menon::front(s), nullptr);
    s.push_back('a');
    BOOST_TEST_EQ(menon::front(s), s.c_str());
    s.push_back('b');
    s.push_back('c');
    s.push_back('d');
    BOOST_TEST_EQ(menon::front(s), s.c_str());
  }
  { // 配列の場合
    int a[10] {};
    BOOST_TEST_EQ(menon::front(a), &a[0]);
  }
}

// back関数のテストコード
void test_back()
{
  { // vectorの場合
    std::vector<int> v;
    BOOST_TEST_EQ(menon::back(v), nullptr);
    v.push_back(1);
    BOOST_TEST_EQ(menon::back(v), v.data());
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    BOOST_TEST_EQ(menon::back(v), &*v.rbegin());
  }
  { // listの場合
    std::list<int> l;
    BOOST_TEST_EQ(menon::back(l), nullptr);
    l.push_back(1);
    BOOST_TEST_EQ(menon::back(l), &*l.begin());
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    BOOST_TEST_EQ(menon::back(l), &*l.rbegin());
  }
  { // stringの場合
    std::string s;
    BOOST_TEST_EQ(menon::back(s), nullptr);
    s.push_back('a');
    BOOST_TEST_EQ(menon::back(s), s.c_str());
    s.push_back('b');
    s.push_back('c');
    s.push_back('d');
    BOOST_TEST_EQ(menon::back(s), &*s.rbegin());
  }
  { // 配列の場合
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
