#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>

int main()
{
  using namespace std::literals::string_view_literals;
  using namespace std::literals::string_literals;
  {
    auto t = { "abc"s, "def"s, "ghi"s };
    BOOST_TEST_EQ(menon::implode(",", t), "abc,def,ghi"s);
  }
  {
    auto t = { "abc"s, "def"s, "ghi"s };
    BOOST_TEST_EQ(menon::implode(","sv, t), "abc,def,ghi"s);
  }
  {
    BOOST_TEST_EQ(menon::implode(",", { "abc"s, "def"s, "ghi"s }), "abc,def,ghi"s);
  }
  {
    BOOST_TEST_EQ(menon::implode(","s, { "abc"s, "def"s, "ghi"s }), "abc,def,ghi"s);
  }
  {
    std::vector t = { "abc"s, "def"s, "ghi"s };
    BOOST_TEST_EQ(menon::implode(",", t.begin(), t.end()), "abc,def,ghi"s);
  }
  return boost::report_errors();
}
