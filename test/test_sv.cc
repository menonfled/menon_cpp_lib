// test_sv.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals::string_view_literals;
  using namespace std::literals::string_literals;
  char s[] = "abc";

  // 文字列リテラルおよびstring_viewからの変換
  constexpr auto r1 = menon::sv("abc");
  constexpr auto r2 = menon::sv("abc"sv);
  BOOST_TEST_EQ(r1, r2);
  constexpr auto r3 = menon::sv("abc", 2);
  BOOST_TEST_EQ(r3, "ab"s);

  // 文字からの変換
  BOOST_TEST_EQ(menon::sv('a'), "a"sv);

  // nullptrおよび文字配列からの変換
  BOOST_TEST_EQ(menon::sv((char const*)nullptr, 2), ""sv);
  BOOST_TEST_EQ(menon::sv(s, 2), "ab"sv);

  // nullptr、文字配列および空文字列からの変換
  BOOST_TEST_EQ(menon::sv((char const*)nullptr), ""sv);
  BOOST_TEST_EQ(menon::sv(s), "abc"sv);
  BOOST_TEST_EQ(menon::sv(""), ""sv);

  // string_viewおよびstringからの変換
  BOOST_TEST_EQ(menon::sv("abc"sv), "abc"sv);
  BOOST_TEST_EQ(menon::sv("abc"s), "abc"sv);
#if MENON_HAS_BOOST
  // boost::string_viewからの変換
  BOOST_TEST_EQ(menon::sv(boost::string_view("abc")), "abc"sv);
#endif
#if MENON_HAS_GSL
  // gsl::string_spanからの変換
  BOOST_TEST_EQ(menon::sv(gsl::basic_string_span<char>(s, 3)), "abc"sv);
#endif

  { // sv_to_array関数のテストコード
    constexpr auto sv = "abcde"sv;
    constexpr auto a = menon::sv_to_array<3>("abcde"sv);
    BOOST_TEST_ALL_EQ(a.begin(), a.end(), sv.begin(), sv.begin() + 3);
  }
  return boost::report_errors();
}
