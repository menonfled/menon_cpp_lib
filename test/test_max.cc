// test_max.cc
#include "menon/utility.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

int main()
{
  using namespace std::literals;

  // max関数のつとコード
  { // int型どうしのテストコード
    constexpr auto r = menon::max(1, 2);
    BOOST_TEST_EQ(r, 2);
  }
  { // 符号付き整数型どうしのテストコード
    constexpr auto r = menon::max(1, 2L);
    BOOST_TEST_EQ(r, 2L);
  }
  { // 浮動小数点型どうしのテストコード
    constexpr double x = 1.23;
    constexpr double y = 2.34f;
    constexpr auto r = menon::max(x, y);
    BOOST_TEST_EQ(r, y);
  }
  { // 浮動小数点型と整数型が混在する場合のテストコード
    constexpr double x = 1.23;
    constexpr int y = 2;
    constexpr auto r = menon::max(x, y);
    BOOST_TEST_EQ(r, y);
  }
  { // string_viewどうしのテストコード
    constexpr auto r = menon::max("abc"sv, "def"sv);
    BOOST_TEST_EQ(r, "def"sv);
  }
  { // int型3引数のテストコード
    constexpr auto r = menon::max(1, 2, 3);
    BOOST_TEST_EQ(r, 3);
  }
  { // 符号付き整数型5引数のテストコード
    constexpr auto r = menon::max(1, 2, 3, 4L, 5LL);
    BOOST_TEST_EQ(r, 5LL);
  }

  // min関数のテストコード
  { // int型どうしのテストコード
    constexpr auto r = menon::min(1, 2);
    BOOST_TEST_EQ(r, 1);
  }
  { // 符号付き整数型どうしのテストコード
    constexpr auto r = menon::min(1, 2L);
    BOOST_TEST_EQ(r, 1L);
  }
  { // 浮動小数点型どうしのテストコード
    constexpr double x = 1.23;
    constexpr double y = 2.34f;
    constexpr auto r = menon::min(x, y);
    BOOST_TEST_EQ(r, x);
  }
  { // 浮動小数点型と整数型が混在する場合のテストコード
    constexpr unsigned x = 1u;
    constexpr double y = 2.34f;
    constexpr auto r = menon::min(x, y);
    BOOST_TEST_EQ(r, x);
  }
  { // string_viewどうしのテストコード
    constexpr auto r = menon::min("abc"sv, "def"sv);
    BOOST_TEST_EQ(r, "abc"sv);
  }
  { // int型3引数のテストコード
   constexpr auto r = menon::min(1, 2, 3);
    BOOST_TEST_EQ(r, 1);
  }
  { // 符号付き整数型5引数のテストコード
    constexpr auto r = menon::min(-1LL, 0L, 1, 2, 3);
    BOOST_TEST_EQ(r, -1LL);
  }
  return boost::report_errors();
}