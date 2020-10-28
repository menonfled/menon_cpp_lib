// test_append.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <list>
#include <deque>

int main()
{
  auto il = { 1, 2, 3, 4, 5, 6 };

  { // vectorに対するテストコード
    std::vector<int> v{ 1, 2, 3 };
    std::vector<int> t { 4, 5, 6 };
    menon::append(t, v);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), il.begin(), il.end());
  }
  { // listに対するテストコード
    std::list<int> l { 1, 2, 3 };
    std::vector<int> t { 4, 5, 6 };
    menon::append(t, l);
    BOOST_TEST_ALL_EQ(l.cbegin(), l.cend(), il.begin(), il.end());
  }
  { // dequeに対するテストコード
    std::deque<int> dq{ 1, 2, 3 };
    std::vector<int> t { 4, 5, 6 };
    menon::append(t, dq);
    BOOST_TEST_ALL_EQ(dq.cbegin(), dq.cend(), il.begin(), il.end());
  }
  return boost::report_errors();
}