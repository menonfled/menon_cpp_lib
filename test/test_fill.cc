// test_fill.cc
#include "menon/algorithm.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>

// fill関数のテストコード
void test_fill()
{
  { // 列コンテナに対するテスト
    std::vector<int> v;
    v.resize(100);
    menon::fill(v, 123);
    BOOST_TEST(std::all_of(v.cbegin(), v.cend(), [](auto value) {
      return value == 123;
    }));
  }
  { // arrayに対するテスト
    std::array<int, 100> a;
    menon::fill(a, 123);
    BOOST_TEST(std::all_of(a.cbegin(), a.cend(), [](auto value) {
      return value == 123;
    }));
  }
  { // 配列に対するテスト
    int a[100];
    menon::fill(a, 123);
    BOOST_TEST(std::all_of(std::cbegin(a), std::cend(a), [](auto value) {
      return value == 123;
    }));
  }
  { // bitsetに対するテスト
    std::bitset<100> bs;
    menon::fill(bs, true);
    BOOST_TEST(bs.all());
    menon::fill(bs, false);
    BOOST_TEST(bs.none());
  }
}

int main()
{
  test_fill();
  return boost::report_errors();
}
