// test_strlen.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  std::string s = "abcdefghi";
  std::size_t n = s.size();

  // 基本的な使い方
  constexpr auto r1 = menon::strlen("abcde");
  BOOST_TEST_EQ(r1, 5);
  constexpr auto r2 = menon::strlen("abcde", 3);
  BOOST_TEST_EQ(r2, 3);
  constexpr auto r3 = menon::strlen("abcde"sv);
  BOOST_TEST_EQ(r3, 5);

  // char配列の長さの上限を指定
  {
    char const s[16] = "abc"; 
    BOOST_TEST_EQ(menon::strlen(s, 16), 3);
  }

  // stringおよびstring_view
  BOOST_TEST_EQ(menon::strlen(s), n);
  BOOST_TEST_EQ(menon::strlen(s.c_str()), n);
  BOOST_TEST_EQ(menon::strlen(s.c_str(), s.size()), n);
  BOOST_TEST_EQ(menon::strlen(std::string_view(s)), n);

  // stringおよびstring_viewの長さの上限を指定
  BOOST_TEST_EQ(menon::strnlen(s, n), n);
  BOOST_TEST_EQ(menon::strnlen(s, 4), 4);
  BOOST_TEST_EQ(menon::strnlen(s, 100), n);
  BOOST_TEST_EQ(menon::strnlen(s.c_str(), n), n);
  BOOST_TEST_EQ(menon::strnlen(s.c_str(), s.size()), n);
  BOOST_TEST_EQ(menon::strnlen(s.c_str(), 5), 5);
  BOOST_TEST_EQ(menon::strnlen(s.c_str(), 100), n);
  BOOST_TEST_EQ(menon::strnlen(std::string_view(s), n), n);
  BOOST_TEST_EQ(menon::strnlen(std::string_view(s), 5), 5);
  BOOST_TEST_EQ(menon::strnlen(std::string_view(s), 100), n);

  return boost::report_errors();
}
