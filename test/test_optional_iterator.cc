#include "menon/iterator.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>
#include <vector>

// TODO テストコードを追加
int main()
{
  using namespace std::literals;

  {
    constexpr auto sv = "abcde"sv;
    constexpr menon::optional_iterator<std::string_view::iterator> t(sv.begin());
    BOOST_TEST(t);
    BOOST_TEST_NOT(!t);
  }

  return boost::report_errors();
}
