// test_assign.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <list>
#include <deque>

int main()
{
  std::vector<int> v{ 1, 2, 3 };
  { // vectorに対するテストコード
    std::vector<int> t;
    menon::assign(v, t);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), t.cbegin(), t.cend());
  }
  { // listに対するテストコード
    std::list<int> t;
    menon::assign(v, t);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), t.cbegin(), t.cend());
  }
  { // dequeに対するテストコード
    std::deque<int> t;
    menon::assign(v, t);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), t.cbegin(), t.cend());
  }
  return boost::report_errors();
}