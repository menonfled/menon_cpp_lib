// test_mb_external_encoding.cc
#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <iostream>

int main()
{
  // default_encoding_keyのテストコード
  BOOST_TEST(menon::detail::default_encoding_key >= 0);
  BOOST_TEST_CSTR_EQ(menon::mb_external_encoding(), menon::detail::encoding_list[menon::detail::default_encoding_key]);

#if defined(_MSC_VER) || (defined(__MINGW32__) && !defined(__clang__))
  // Windows向けのテストコード
  BOOST_TEST_CSTR_EQ(menon::mb_external_encoding(), "CP932");
  // 外部エンコーディングをEUC-JPに設定
  BOOST_TEST_CSTR_EQ(menon::mb_external_encoding("EUC-JP"), "CP932");
#else
  // Windows以外向けのテストコード
  BOOST_TEST_CSTR_EQ(menon::mb_external_encoding(), "UTF-8");
  // 外部エンコーディングをEUC-JPに設定
  BOOST_TEST_CSTR_EQ(menon::mb_external_encoding("EUC-JP"), "UTF-8");
#endif
  // 外部エンコーディングEUC-JPになっていることを確認
  BOOST_TEST_CSTR_EQ(menon::mb_external_encoding(), "EUC-JP");
  // 不正なエンコーディングを指定した場合のエラー処理
  BOOST_TEST_EQ(menon::mb_external_encoding("xxx"), nullptr);
  return boost::report_errors();
}
