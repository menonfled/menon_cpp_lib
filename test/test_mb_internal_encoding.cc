#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <iostream>

int main()
{
  BOOST_TEST(menon::detail::default_encoding_key >= 0);
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), menon::detail::encoding_list[menon::detail::default_encoding_key]);
#if defined(_MSC_VER) || (defined(__MINGW32__) && !defined(__clang__))
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), "CP932");
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding("EUC-JP"), "CP932");
#else
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), "UTF-8");
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding("EUC-JP"), "UTF-8");
#endif
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), "EUC-JP");
  BOOST_TEST_EQ(menon::mb_internal_encoding("xxx"), nullptr);
  return boost::report_errors();
}
