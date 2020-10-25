#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <list>

int main()
{
  auto il = { 1, 2, 3, 4, 5, 6 };
  {
    std::vector<int> v{ 1, 2, 3 };
    std::vector<int> t { 4, 5, 6 };
    menon::append(t, v);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), il.begin(), il.end());
  }
  {
    std::list<int> l { 1, 2, 3 };
    std::vector<int> t { 4, 5, 6 };
    menon::append(t, l);
    BOOST_TEST_ALL_EQ(l.cbegin(), l.cend(), il.begin(), il.end());
  }
  return boost::report_errors();
}