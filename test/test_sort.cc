﻿#include "menon/algorithm.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <string>
#include <string_view>
#include <numeric>
#include <random>
#include <cstring>

std::random_device seed_gen;
std::mt19937 engine(seed_gen());

void test_sort()
{
  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    menon::sort(v);
    BOOST_TEST_ALL_EQ(v.begin(), v.end(), v2.begin(), v2.end());
  }
  {
    int a[256];
    std::iota(std::begin(a), std::end(a), 0);
    int b[256];
    std::memcpy(b, a, sizeof(a));
    std::shuffle(std::begin(a), std::end(a), engine);
    menon::sort(a);
    BOOST_TEST_ALL_EQ(std::cbegin(a), std::cend(a), std::cbegin(b), std::cend(b));
  }
  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    std::list<int> l(v.cbegin(), v.cend());
    menon::sort(l);
    BOOST_TEST_ALL_EQ(l.begin(), l.end(), v2.begin(), v2.end());
  }

  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    menon::sort(v, std::greater<int>());
    std::reverse(v2.begin(), v2.end());
    BOOST_TEST_ALL_EQ(v.begin(), v.end(), v2.begin(), v2.end());
  }
  {
    int a[256];
    std::iota(std::begin(a), std::end(a), 0);
    int b[256];
    std::memcpy(b, a, sizeof(a));
    std::shuffle(std::begin(a), std::end(a), engine);
    menon::sort(a, std::greater<int>());
    std::reverse(std::begin(b), std::end(b));
    BOOST_TEST_ALL_EQ(std::cbegin(a), std::cend(a), std::cbegin(b), std::cend(b));
  }
  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    std::list<int> l(v.cbegin(), v.cend());
    menon::sort(l, std::greater<int>());
    std::reverse(v2.begin(), v2.end());
    BOOST_TEST_ALL_EQ(l.begin(), l.end(), v2.begin(), v2.end());
  }
}

void test_stable_sort()
{
  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    menon::stable_sort(v);
    BOOST_TEST_ALL_EQ(v.begin(), v.end(), v2.begin(), v2.end());
  }
  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    std::list<int> l(v.cbegin(), v.cend());
    menon::stable_sort(l);
    BOOST_TEST_ALL_EQ(l.begin(), l.end(), v2.begin(), v2.end());
  }

  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    menon::stable_sort(v, std::greater<int>());
    std::reverse(v2.begin(), v2.end());
    BOOST_TEST_ALL_EQ(v.begin(), v.end(), v2.begin(), v2.end());
  }
  {
    std::vector<int> v;
    v.resize(256);
    std::iota(v.begin(), v.end(), 0);
    auto v2 = v;
    std::shuffle(v.begin(), v.end(), engine);
    std::list<int> l(v.cbegin(), v.cend());
    menon::stable_sort(l, std::greater<int>());
    std::reverse(v2.begin(), v2.end());
    BOOST_TEST_ALL_EQ(l.begin(), l.end(), v2.begin(), v2.end());
  }
}

int main()
{
  test_sort();
  test_stable_sort();
  return boost::report_errors();
}