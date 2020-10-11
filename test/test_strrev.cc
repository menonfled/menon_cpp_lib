#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  using namespace std::literals;

  BOOST_TEST_EQ(menon::strrev("abcde"), "edcba");
  BOOST_TEST_EQ(menon::strrev("abcde"s), "edcba");
  BOOST_TEST_EQ(menon::strrev("abcde"sv), "edcba");
  char const* s = "abcde";
  BOOST_TEST_EQ(menon::strrev(s), "edcba");

  BOOST_TEST(menon::strrev(L"abcde") == L"edcba");
  BOOST_TEST(menon::strrev(L"abcde"s) == L"edcba");
  BOOST_TEST(menon::strrev(L"abcde"sv) == L"edcba");
  wchar_t const* wcs = L"abcde";
  BOOST_TEST(menon::strrev(wcs) == L"edcba");

  return boost::report_errors();
}
