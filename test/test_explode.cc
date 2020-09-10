#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

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
  return boost::report_errors();
}
