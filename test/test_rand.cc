// test_rand.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> v1, v2;
  constexpr int n = 0x8000;

  // 生成した乱数列を2組作る。
  for (int i = 0; i < n; i++)
    v1.push_back(menon::rand());
  for (int i = 0; i < n; i++)
    v2.push_back(menon::rand());

  // 各欄数列のサイズを確認
  BOOST_TEST_EQ(v1.size(), n);
  BOOST_TEST_EQ(v2.size(), n);

  // 2つの乱数列が異なることを確認
  BOOST_TEST_NOT(std::equal(v1.cbegin(), v1.cend(), v2.cbegin()));

  return boost::report_errors();
}