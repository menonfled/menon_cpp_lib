#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <list>

int main()
{
  std::vector<int> v{ 1, 2, 3 };
  {
    std::vector<int> t;
    menon::assign(v, t);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), t.cbegin(), t.cend());
  }
  {
    std::list<int> t;
    menon::assign(v, t);
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), t.cbegin(), t.cend());
  }
  return boost::report_errors();
}