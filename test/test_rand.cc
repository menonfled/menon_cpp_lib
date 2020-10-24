#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v1, v2;
  constexpr int n = 0x7fff;

  for (int i = 0; i <= n; i++)
    v1.push_back(menon::rand());
  for (int i = 0; i <= n; i++)
    v2.push_back(menon::rand());

  BOOST_TEST_GT(v1.size(), n / 2);
  BOOST_TEST_GT(v2.size(), n / 2);
  BOOST_TEST_NOT(std::equal(v1.cbegin(), v1.cend(), v2.cbegin()));

  return boost::report_errors();
}