﻿#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  {
    std::string s = "abcdefghi";
    std::string_view sv = s;

    BOOST_TEST(menon::strcmp(s, sv) == 0);
    BOOST_TEST(menon::strcmp(s, "fgnrk") < 0);
    BOOST_TEST(menon::strcmp(s, "aaekj") > 0);
  }
  {
    std::wstring s = L"abcdefghi";
    std::wstring_view sv = s;

    BOOST_TEST(menon::strcmp(s, sv) == 0);
    BOOST_TEST(menon::strcmp(s, L"fgnrk") < 0);
    BOOST_TEST(menon::strcmp(s, L"aaekj") > 0);
  }
  return boost::report_errors();
}
