#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>

int main()
{
  using namespace std::literals;

  {
    BOOST_TEST(menon::starts_with("abcde", "ab"));
    BOOST_TEST_NOT(menon::starts_with("abcde", "xy"));
  }
  {
    BOOST_TEST(menon::starts_with("abcde", 'a'));
    BOOST_TEST_NOT(menon::starts_with("abcde", 'x'));
  }
  return boost::report_errors();
}