// test_mb_convert_encoding.cc
#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  char const* s = "文字エンコーディングの変換テスト";
  char const* cp932_s = "\x95\xb6\x8e\x9a\x83\x47\x83\x93\x83\x52\x81\x5b\x83\x66\x83\x42\x83\x93\x83\x4f\x82\xcc\x95\xcf\x8a\xb7\x83\x65\x83\x58\x83\x67";
  char const* utf8_s = "\xe6\x96\x87\xe5\xad\x97\xe3\x82\xa8\xe3\x83\xb3\xe3\x82\xb3\xe3\x83\xbc\xe3\x83\x87\xe3\x82\xa3\xe3\x83\xb3\xe3\x82\xb0\xe3\x81\xae\xe5\xa4\x89\xe6\x8f\x9b\xe3\x83\x86\xe3\x82\xb9\xe3\x83\x88";
  char const* eucjp_s = "\xca\xb8\xbb\xfa\xa5\xa8\xa5\xf3\xa5\xb3\xa1\xbc\xa5\xc7\xa5\xa3\xa5\xf3\xa5\xb0\xa4\xce\xca\xd1\xb4\xb9\xa5\xc6\xa5\xb9\xa5\xc8";
  char16_t const* c16_s = u"\u6587\u5b57\u30a8\u30f3\u30b3\u30fc\u30c7\u30a3\u30f3\u30b0\u306e\u5909\u63db\u30c6\u30b9\u30c8";
  char32_t const* c32_s = U"\u6587\u5b57\u30a8\u30f3\u30b3\u30fc\u30c7\u30a3\u30f3\u30b0\u306e\u5909\u63db\u30c6\u30b9\u30c8";
  wchar_t const* wcs_s = L"\u6587\u5b57\u30a8\u30f3\u30b3\u30fc\u30c7\u30a3\u30f3\u30b0\u306e\u5909\u63db\u30c6\u30b9\u30c8";

  // char文字列からの変換
  BOOST_TEST_CSTR_EQ(menon::mb_convert_encoding(s, "CP932").c_str(), cp932_s);
  BOOST_TEST_CSTR_EQ(menon::mb_convert_encoding(s, "UTF-8", "CP932").c_str(), utf8_s);

  // EUC-JPからの変換
  BOOST_TEST_CSTR_EQ(menon::mb_convert_encoding(eucjp_s, "CP932", "EUC-JP").c_str(), cp932_s);

  // UTF-16空の変換
  BOOST_TEST(menon::mb_convert_encoding<char>(c16_s, "CP932") == cp932_s);

  // UTF-32からの変換
  BOOST_TEST(menon::mb_convert_encoding<char>(c32_s, "UTF-8") == utf8_s);

  // char文字列からUTF-32への変換
  BOOST_TEST(menon::mb_convert_encoding<char32_t>(s, menon::get_internal_encoding<char32_t>()) == c32_s);

  // char文字列からワイド文字列への変換
  BOOST_TEST(menon::mb_convert_encoding<wchar_t>(s, menon::get_internal_encoding<wchar_t>()) == wcs_s);

  // ワイド文字列からchar文字列への変換
  BOOST_TEST(menon::mb_convert_encoding<char>(wcs_s, "UTF-8") == utf8_s);

  // byte配列からchar文字列への変換
  std::byte bytes[] = { std::byte('a'), std::byte('b'), std::byte('c') };
  BOOST_TEST_CSTR_EQ(menon::mb_convert_encoding<char>(bytes, 3, "UTF-8", "ASCII").c_str(), "abc");

  return boost::report_errors();
}
