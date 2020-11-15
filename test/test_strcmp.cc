// test_strcmp.cc
#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  // ナロー文字列のテストコード
  {
    std::string s = "abcdefghi";
    std::string_view sv = s;

    // strcmp関数のテストコード
    BOOST_TEST(menon::strcmp(s, sv) == 0);
    BOOST_TEST(menon::strcmp(s, "fgnrk") < 0);
    BOOST_TEST(menon::strcmp(s, "aaekj") > 0);

    // strncmp関数のテストコード
    BOOST_TEST(menon::strncmp(s, sv, 5) == 0);
    BOOST_TEST(menon::strncmp(s, "abcrtylk", 3) == 0);
    BOOST_TEST(menon::strncmp(s, "fgnrk", 5) < 0);
    BOOST_TEST(menon::strncmp(s, "aaekj", 10) > 0);

    // strcasecmp関数のテストコード
    BOOST_TEST(menon::strcasecmp(s, sv) == 0);
    BOOST_TEST(menon::strcasecmp(s, "fgnrk") < 0);
    BOOST_TEST(menon::strcasecmp(s, "aaekj") > 0);
    BOOST_TEST(menon::strcasecmp(s, "AbcDefGhi") == 0);
    BOOST_TEST(menon::strcasecmp(s, "FgNrk") < 0);
    BOOST_TEST(menon::strcasecmp(s, "aAeKJ") > 0);

    // strncasecmp関数のテストコード
    BOOST_TEST(menon::strncasecmp(s, sv, 5) == 0);
    BOOST_TEST(menon::strncasecmp(s, "AbCrTyLK", 3) == 0);
    BOOST_TEST(menon::strncasecmp(s, "fgnrk", 5) < 0);
    BOOST_TEST(menon::strncasecmp(s, "aaekj", 5) > 0);
    BOOST_TEST(menon::strncasecmp(s, "AbcDefGhi", 5) == 0);
    BOOST_TEST(menon::strncasecmp(s, "FgNrk", 5) < 0);
    BOOST_TEST(menon::strncasecmp(s, "aAeKJ", 10) > 0);
  }

  // ワイド文字列のテストコード
  {
    std::wstring s = L"abcdefghi";
    std::wstring_view sv = s;

    // strcmp関数のテストコード
    BOOST_TEST(menon::strcmp(s, sv) == 0);
    BOOST_TEST(menon::strcmp(s, L"fgnrk") < 0);
    BOOST_TEST(menon::strcmp(s, L"aaekj") > 0);

    // strncmp関数のテストコード
    BOOST_TEST(menon::strncmp(s, sv, 5) == 0);
    BOOST_TEST(menon::strncmp(s, L"abcrtylk", 3) == 0);
    BOOST_TEST(menon::strncmp(s, L"fgnrk", 5) < 0);
    BOOST_TEST(menon::strncmp(s, L"aaekj", 10) > 0);

    // strcasecmp関数のテストコード
    BOOST_TEST(menon::strcasecmp(s, sv) == 0);
    BOOST_TEST(menon::strcasecmp(s, L"fgnrk") < 0);
    BOOST_TEST(menon::strcasecmp(s, L"aaekj") > 0);
    BOOST_TEST(menon::strcasecmp(s, L"AbcDefGhi") == 0);
    BOOST_TEST(menon::strcasecmp(s, L"FgNrk") < 0);
    BOOST_TEST(menon::strcasecmp(s, L"aAeKJ") > 0);

    // strncasecmp関数のテストコード
    BOOST_TEST(menon::strncasecmp(s, sv, 5) == 0);
    BOOST_TEST(menon::strncasecmp(s, L"AbCrTyLK", 3) == 0);
    BOOST_TEST(menon::strncasecmp(s, L"fgnrk", 5) < 0);
    BOOST_TEST(menon::strncasecmp(s, L"aaekj", 5) > 0);
    BOOST_TEST(menon::strncasecmp(s, L"AbcDefGhi", 5) == 0);
    BOOST_TEST(menon::strncasecmp(s, L"FgNrk", 5) < 0);
    BOOST_TEST(menon::strncasecmp(s, L"aAeKJ", 10) > 0);
  }
  return boost::report_errors();
}
