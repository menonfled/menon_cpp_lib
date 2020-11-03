// test_for_each_n.cc
#include "menon/algorithm.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <list>

void test_for_each_n()
{
  std::vector v = { 1, 2, 3, 4, 5, };
  std::size_t n = v.size();

  { // vectorからlistへのコピー
    std::list<int> l;
    menon::for_each_n(v.cbegin(), n, [&l](auto iter, auto i) {
      l.push_back(iter[i]);
    });
    BOOST_TEST_ALL_EQ(l.cbegin(), l.cend(), v.cbegin(), v.cend());
  }

  { // vectorから3を除去
    menon::for_each_n(v.begin(), n, [&v](auto iter, auto& i) {
      if (iter[i] == 3)
      {
        v.erase(iter + i);
        --i;
      }
    });
    auto il = { 1, 2, 4, 5, };
    BOOST_TEST_ALL_EQ(v.cbegin(), v.cend(), il.begin(), il.end());
  }
}

int main()
{
  test_for_each_n();
  return boost::report_errors();
}
