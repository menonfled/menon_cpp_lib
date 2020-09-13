/// @file   menon/bits/unicode.hh
/// @author @menonfled
/// Unicode関連処理の宣言・定義
#ifndef MENON_BITS_UNICODE_HH_
#define MENON_BITS_UNICODE_HH_
#pragma once

#include "menon/bits/config.hh"
#include <array>

/// バイト順マーク（BOM）
/// 文字列リテラルの先頭に付加することで使用する。
/// u8""またはu""を前置することでchar8_tまたはchar16_t型の文字列にすることができる。 
#define MENON_BYTE_ORDER_MARK "\ufeff"

namespace menon
{
  /// char32_tからchar16_tへの変換
  /// @param[in]  c32   char32_t型の文字
  /// @return     char16_t型の文字を返す。
  /// サロゲートペアを考慮し、結果は2要素のarrayとして返す。
  /// 不要な要素にはナル文字を格納する。
  inline auto c32_to_c16(char32_t c32)
  {
    std::array<char16_t, 2> c16;
    if (c32 < 0x10000)
    {
      c16[0] = static_cast<char16_t>(c32);
      c16[1] = u'\0';
    }
    else
    {
      c16[0] = static_cast<char16_t>((c32 - 0x10000) / 0x400 + 0xd800);
      c16[1] = static_cast<char16_t>((c32 - 0x10000) % 0x400 + 0xdc00);
    }
    return c16; 
  }

  /// char32_tからchar8_tへの変換
  /// @param[in]  c32   char32_t型の文字
  /// @return     char8_t型の文字を返す。
  /// 値に応じて結果のarrayには1～4要素を格納する。
  /// 不要な要素にはナル文字を格納する。
  /// c32が不正な値の場合は全要素ナル文字を格納する。
  inline auto c32_to_c8(char32_t c32)
  {
    std::array<char8_t, 4> c8 {};

    if ((0xd800 <= c32 && c32 <= 0xdbff) && (0xdc00 <= c32 && c32 <= 0xdfff))
      return c8;

    if (c32 <= 0x7f)
    {
      c8[0] = static_cast<char8_t>(c32);
    }
    else if (c32 <= 0x7ff)
    {
      c8[0] = static_cast<char8_t>((c32 >> 6) | 0b1100'0000);
      c8[1] = static_cast<char8_t>((c32 & 0x3f) | 0b1000'0000);
    }
    else if (c32 <= 0xffff)
    {
      c8[0] = static_cast<char8_t>((c32 >> 12) | 0b1110'0000);
      c8[1] = static_cast<char8_t>(((c32 >> 6) & 0x3f) | 0b1000'0000);
      c8[2] = static_cast<char8_t>((c32 & 0x3f) | 0b1000'0000);
    }
    else if (c32 <= 0x0010ffff)
    {
      c8[0] = static_cast<char8_t>((c32 >> 18) | 0b1111'0000);
      c8[1] = static_cast<char8_t>(((c32 >> 12) & 0x3f) | 0b1000'0000);
      c8[1] = static_cast<char8_t>(((c32 >> 6) & 0x3f) | 0b1000'0000);
      c8[2] = static_cast<char8_t>((c32 & 0x3f) | 0b1000'0000);
    }
    return c8;
  }

  /// char16_tからchar32_tへの変換
  /// @param[in]  c16   char16_t型の文字配列
  /// @param[in]  n     c16が指す配列の要素数
  /// @return     char32_t型の文字を返す。変換に失敗した場合はナル文字を返す。
  /// サロゲートペアを考慮し、引数は2要素の配列として受け取る。
  /// サロゲートペアではない場合は最初の1要素のみを使用し、2要素目は無視する。
  inline auto c16_to_c32(char16_t const* c16, std::size_t n)
  {
    char32_t c32 = U'\0';
    char16_t h = u'\0';
    char16_t l = u'\0';

    if (n > 0)
      h = c16[0];
    if (n > 1)
      l = c16[1];

    if (0xd800 <= h && h <= 0xdbff)
    {
      if (0xdc00 <= l && l <= 0xdfff)
        c32 = static_cast<char32_t>(0x10000 + (h - 0xd800) * 0x400 + (l - 0xdc00));
    }
    else if (l < 0xdc00 || 0xdfff < l)
    {
      c32 = static_cast<char32_t>(h);
    }
    return c32;
  }

  /// char16_tからchar32_tへの変換
  /// @param[in]  c16   char16_t型の文字
  /// @return     char32_t型の文字を返す。変換に失敗した場合はナル文字を返す。
  /// サロゲートペアには対応しない。
  /// サロゲートペアの片側を指定した場合はナル文字を返す。
  inline auto c16_to_c32(char16_t c16)
  {
    if ((0xd800 <= c16 && c16 <= 0xdbff) && (0xdc00 <= c16 && c16 <= 0xdfff))
      return U'\0';
    return static_cast<char32_t>(c16);
  }

  /// char8_tからchar32_tへの変換
  /// @param[in]  c8    char8_t型の文字配列
  /// @param[in]  n     c8が指す配列の要素数
  /// @return     char32_t型の文字を返す。変換に失敗した場合はナル文字を返す。
  auto c8_to_c32(char8_t const* c8, std::size_t n)
  {
    char32_t c32 = U'\0';

    if (n > 0 && c8[0] <= 0x7f)
    {
      c32 = static_cast<char32_t>(c8[0]);
    }
    else if (n > 1 && ((c8[0] & 0b1110'0000) == 0b1100'0000))
    {
      if ((c8[1] & 0b1100'0000) == 0b1000'0000)
      {
        c32 = (c8[0] & 0b0001'1111) << 6 | (c8[1] & 0b0011'1111);
      }
    }
    else if (n > 1 && (c8[0] & 0b1111'0000) == 0b1110'0000)
    {
      if (((c8[1] & 0b1100'0000) == 0b1000'0000) && ((c8[2] & 0b1100'0000) == 0b1000'0000))
        c32 = (c8[0] & 0b0000'1111) << 12 | (c8[1] & 0b0011'1111) << 6 | (c8[2] & 0b0011'1111);
    }
    else if (n > 2 && (c8[0] & 0b1111'1000) == 0b1111'0000)
    {
      if (((c8[1] & 0b1100'0000) == 0b1000'0000) && ((c8[2] & 0b1100'0000) == 0b1000'0000) && ((c8[3] & 0b1100'0000) == 0b1000'0000))
        c32 = (c8[0] & 0b0000'1111) << 18 | (c8[1] & 0b0011'1111) << 12 | (c8[2] & 0b0011'1111) << 6 | (c8[3] & 0b0011'1111);
    }
    return c32;
  }

  /// char8_tからchar32_tへの変換
  /// @param[in]  c8    char8_t型の文字
  /// @return     char32_t型の文字を返す。変換に失敗した場合はナル文字を返す。
  inline auto c8_to_c32(char8_t c8)
  {
    char32_t c32 = U'\0';

    if (c8 <= 0x7f)
      c32 = c8;
    return c32;
  }
}

#endif  // !MENON_BITS_UNICODE_HH_
