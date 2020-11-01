// test_explode.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <deque>
#include <list>

int main()
{
  using namespace std::literals::string_view_literals;
  { // 基本的な使い方
    auto r = menon::explode(",", "abc,de,,fg");
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }
  { // limitに正の値を指定
    auto r = menon::explode(",", "abc,de,,fg", 2);
    std::vector t = { "abc"sv, "de,,fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }
  { // limitに負の値を指定
    auto r = menon::explode(",", "abc,de,,fg", -2);
    std::vector t = { "abc"sv, "de"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }
  { // delimiterに（文字列ではなく）文字を指定
    auto r = menon::explode(',', "abc,de,,fg");
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }

  { // 第2引数にvector<string>を指定
    std::vector<std::string> r;
    auto& r2 = menon::explode(",", "abc,de,,fg", r);
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  { // 第2引数にdeque<string>を指定
    std::deque<std::string> r;
    auto& r2 = menon::explode(",", "abc,de,,fg", r, 2);
    std::vector t = { "abc"sv, "de,,fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  { // 第2引数にlist<string>を指定
    std::list<std::string> r;
    auto& r2 = menon::explode(",", "abc,de,,fg", r, -2);
    std::vector t = { "abc"sv, "de"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  { // 第2引数にvector<string_view>を指定
    std::vector<std::string_view> r;
    auto& r2 = menon::explode(',', "abc,de,,fg", r);
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  return boost::report_errors();
}
