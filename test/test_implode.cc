// test_implode.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <vector>
#include <list>

int main()
{
  using namespace std::literals::string_view_literals;
  using namespace std::literals::string_literals;

  { // string_viewのvectorをナル終端文字列で連結
    std::vector t = { "abc"s, "def"s, "ghi"s };
    BOOST_TEST_EQ(menon::implode(",", t), "abc,def,ghi"s);
  }
  { // string_viewをstring_viewで連結
    auto t = { "abc"s, "def"s, "ghi"s };
    BOOST_TEST_EQ(menon::implode(","sv, t), "abc,def,ghi"s);
  }
  { // string_viewのinitializer_listをナル終端文字列で連結
    BOOST_TEST_EQ(menon::implode(",", { "abc"s, "def"s, "ghi"s }), "abc,def,ghi"s);
  }
  { // string_viewのinitializer_listをstring_viewで連結
    BOOST_TEST_EQ(menon::implode(","s, { "abc"s, "def"s, "ghi"s }), "abc,def,ghi"s);
  }
  { // string_viewのlistをナル終端文字列で連結
    std::list t = { "abc"s, "def"s, "ghi"s };
    BOOST_TEST_EQ(menon::implode(",", t.begin(), t.end()), "abc,def,ghi"s);
  }
  return boost::report_errors();
}
