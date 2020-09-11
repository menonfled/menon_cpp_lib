#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <deque>
#include <list>

int main()
{
  using namespace std::literals::string_view_literals;
  {
    auto r = menon::explode(",", "abc,de,,fg");
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }
  {
    auto r = menon::explode(",", "abc,de,,fg", 2);
    std::vector t = { "abc"sv, "de,,fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }
  {
    auto r = menon::explode(",", "abc,de,,fg", -2);
    std::vector t = { "abc"sv, "de"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }
  {
    auto r = menon::explode(',', "abc,de,,fg");
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
  }

  {
    std::vector<std::string> r;
    auto& r2 = menon::explode(",", "abc,de,,fg", r);
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  {
    std::deque<std::string> r;
    auto& r2 = menon::explode(",", "abc,de,,fg", r, 2);
    std::vector t = { "abc"sv, "de,,fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  {
    std::list<std::string> r;
    auto& r2 = menon::explode(",", "abc,de,,fg", r, -2);
    std::vector t = { "abc"sv, "de"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  {
    std::vector<std::string_view> r;
    auto& r2 = menon::explode(',', "abc,de,,fg", r);
    std::vector t = { "abc"sv, "de"sv, ""sv, "fg"sv };
    BOOST_TEST_ALL_EQ(r.cbegin(), r.cend(), t.cbegin(), t.cend());
    BOOST_TEST_EQ(&r, &r2);
  }
  return boost::report_errors();
}
