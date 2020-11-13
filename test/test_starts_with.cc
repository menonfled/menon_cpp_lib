// test_starts_with.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

// starts_with関数のテストコード
void test_starts_with()
{
  using namespace std::literals;
  { // 第2引数が文字列
    BOOST_TEST(menon::starts_with("abcde", "ab"));
    BOOST_TEST_NOT(menon::starts_with("abcde", "xy"));
    BOOST_TEST(menon::start_with("abcde", "ab"));
    BOOST_TEST_NOT(menon::start_with("abcde", "xy"));
  }
  { // 第2引数が文字
    BOOST_TEST(menon::starts_with("abcde", 'a'));
    BOOST_TEST_NOT(menon::starts_with("abcde", 'x'));
    BOOST_TEST(menon::start_with("abcde", 'a'));
    BOOST_TEST_NOT(menon::start_with("abcde", 'x'));
  }
}

// ends_with関数のテストコード
void test_ends_with()
{
  using namespace std::literals;
  { // 第2引数が文字列
    BOOST_TEST(menon::ends_with("abcde", "de"));
    BOOST_TEST_NOT(menon::ends_with("abcde", "xy"));
    BOOST_TEST(menon::end_with("abcde", "de"));
    BOOST_TEST_NOT(menon::end_with("abcde", "xy"));
  }
  { // 第2引数が文字
    BOOST_TEST(menon::ends_with("abcde", 'e'));
    BOOST_TEST_NOT(menon::ends_with("abcde", 'x'));
    BOOST_TEST(menon::end_with("abcde", 'e'));
    BOOST_TEST_NOT(menon::end_with("abcde", 'x'));
  }
}

int main()
{
  test_starts_with();
  test_ends_with();
  return boost::report_errors();
}