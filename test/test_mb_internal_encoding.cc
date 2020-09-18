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

  constexpr auto char32_encoding = menon::get_internal_encording<char32_t>();
  constexpr auto char16_encoding = menon::get_internal_encording<char16_t>();
#if defined(_MSC_VER) || __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32LE");
  BOOST_TEST_CSTR_EQ(char16_encoding, "UTF-16LE");
#else
  BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32BE");
  BOOST_TEST_CSTR_EQ(char16_encoding, "UTF-16BE");
#endif

  constexpr auto char8_encoding = menon::get_internal_encording<char8_t>();
  BOOST_TEST_CSTR_EQ(char8_encoding, "UTF-8");

  constexpr auto wchar_encoding = menon::get_internal_encording<wchar_t>();
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
  BOOST_TEST_CSTR_EQ(wchar_encoding, "UTF-16LE");
#else
# if defined(_MSC_VER) || __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32LE");
# else
    BOOST_TEST_CSTR_EQ(char32_encoding, "UTF-32BE");
# endif
#endif

  auto char_encoding = menon::get_internal_encording<char>();
  BOOST_TEST_CSTR_EQ(char_encoding, menon::mb_internal_encoding());

  auto schar_encoding = menon::get_internal_encording<signed char>();
  BOOST_TEST_CSTR_EQ(schar_encoding, menon::mb_internal_encoding());

  auto uchar_encoding = menon::get_internal_encording<unsigned char>();
  BOOST_TEST_CSTR_EQ(uchar_encoding, menon::mb_internal_encoding());

  return boost::report_errors();
}
