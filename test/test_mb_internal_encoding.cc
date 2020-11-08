// test_mb_internal_encoding.cc
#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <iostream>

int main()
{
  // default_encoding_keyのテストコード
  BOOST_TEST(menon::detail::default_encoding_key >= 0);
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), menon::detail::encoding_list[menon::detail::default_encoding_key]);

#if defined(_MSC_VER) || (defined(__MINGW32__) && !defined(__clang__))
  // Windows向けのテストコード
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), "CP932");
  // 内部エンコーディングをEUC-JPに設定
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding("EUC-JP"), "CP932");
#else
  // Windows以外向けのテストコード
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), "UTF-8");
  // 内部エンコーディングをEUC-JPに設定
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding("EUC-JP"), "UTF-8");
#endif
  // 内部エンコーディングEUC-JPになっていることを確認
  BOOST_TEST_CSTR_EQ(menon::mb_internal_encoding(), "EUC-JP");
  // 不正なエンコーディングを指定した場合のエラー処理
  BOOST_TEST_EQ(menon::mb_internal_encoding("xxx"), nullptr);

  // デフォルトの内部文字エンコーディングに関するテストコード
  constexpr auto char32_encoding = menon::get_internal_encoding<char32_t>();
  constexpr auto char16_encoding = menon::get_internal_encoding<char16_t>();
#if defined(_MSC_VER) || __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32LE");
  BOOST_TEST_CSTR_EQ(char16_encoding, "UTF-16LE");
#else
  BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32BE");
  BOOST_TEST_CSTR_EQ(char16_encoding, "UTF-16BE");
#endif

  constexpr auto char8_encoding = menon::get_internal_encoding<char8_t>();
  BOOST_TEST_CSTR_EQ(char8_encoding, "UTF-8");

  constexpr auto wchar_encoding = menon::get_internal_encoding<wchar_t>();
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
  BOOST_TEST_CSTR_EQ(wchar_encoding, "UTF-16LE");
#else
# if defined(_MSC_VER) || __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32LE");
# else
    BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32BE");
# endif
#endif

  auto char_encoding = menon::get_internal_encoding<char>();
  BOOST_TEST_CSTR_EQ(char_encoding, menon::mb_internal_encoding());

  auto schar_encoding = menon::get_internal_encoding<signed char>();
  BOOST_TEST_CSTR_EQ(schar_encoding, menon::mb_internal_encoding());

  auto uchar_encoding = menon::get_internal_encoding<unsigned char>();
  BOOST_TEST_CSTR_EQ(uchar_encoding, menon::mb_internal_encoding());

  return boost::report_errors();
}
