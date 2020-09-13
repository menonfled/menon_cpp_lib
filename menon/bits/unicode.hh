/// @file   menon/bits/unicode.hh
/// @author @menonfled
/// Unicode関連処理の宣言・定義
#ifndef MENON_BITS_UNICODE_HH_
#define MENON_BITS_UNICODE_HH_
#pragma once

#include "menon/bits/config.hh"
#include <utility>

/// バイト順マーク（BOM）
/// 文字列リテラルの先頭に付加することで使用する。
/// u8""またはu""を前置することでchar8_tまたはchar16_t型の文字列にすることができる。 
#define MENON_BYTE_ORDER_MARK "\ufeff"

namespace menon
{
  /// char32_tからchar16_tへの変換
  /// @param[in]  c32   char32_t型の文字
  /// @param[out] c16   char16_t文字の格納先配列
  /// @param[in]  n     c16が指す配列の要素数
  /// @return     c16に格納した要素数を返す。
  inline auto c32_to_c16(char32_t c32, char16_t* c16, std::size_t n)
    -> std::size_t
  {
    if (c16 == nullptr)
      return 0;

    if (n > 0 && c32 < 0x10000)
    {
      c16[0] = static_cast<char16_t>(c32);
      n = 1;
    }
    else if (n > 1)
    {
      c16[0] = static_cast<char16_t>((c32 - 0x10000) / 0x400 + 0xd800);
      c16[1] = static_cast<char16_t>((c32 - 0x10000) % 0x400 + 0xdc00);
      n = 2;
    }
    else
    {
      n = 0;
    }
    return n; 
  }

  /// char32_tからchar8_tへの変換
  /// @param[in]  c32   char32_t型の文字
  /// @param[out] c8    char8_t文字の格納先配列
  /// @param[in]  n     c8が指す配列の要素数
  /// @return     c8に格納した要素数を返す。
  inline auto c32_to_c8(char32_t c32, char8_t* c8, std::size_t n)
    -> std::size_t
  {
    if (c8 == nullptr)
      return 0;
    if ((0xd800 <= c32 && c32 <= 0xdbff) && (0xdc00 <= c32 && c32 <= 0xdfff))
      return 0;

    if (n > 0 && c32 <= 0x7f)
    {
      c8[0] = static_cast<char8_t>(c32);
      n = 1;
    }
    else if (n > 1 && c32 <= 0x7ff)
    {
      c8[0] = static_cast<char8_t>((c32 >> 6) | 0b1100'0000);
      c8[1] = static_cast<char8_t>((c32 & 0x3f) | 0b1000'0000);
      n = 2;
    }
    else if (n > 2 && c32 <= 0xffff)
    {
      c8[0] = static_cast<char8_t>((c32 >> 12) | 0b1110'0000);
      c8[1] = static_cast<char8_t>(((c32 >> 6) & 0x3f) | 0b1000'0000);
      c8[2] = static_cast<char8_t>((c32 & 0x3f) | 0b1000'0000);
      n = 3;
    }
    else if (n > 3 && c32 <= 0x0010ffff)
    {
      c8[0] = static_cast<char8_t>((c32 >> 18) | 0b1111'0000);
      c8[1] = static_cast<char8_t>(((c32 >> 12) & 0x3f) | 0b1000'0000);
      c8[1] = static_cast<char8_t>(((c32 >> 6) & 0x3f) | 0b1000'0000);
      c8[2] = static_cast<char8_t>((c32 & 0x3f) | 0b1000'0000);
      n = 4;
    }
    else
    {
      n = 0;
    }
    return n;
  }

  /// char16_tからchar32_tへの変換
  /// @param[in]  c16   char16_t型の文字配列
  /// @param[in]  n     c16が指す配列の要素数
  /// @param[out] c32   変換したchar32_t文字の格納先
  /// @return     c16配列の解析した要素数を返す。
  /// c32がnullptrの場合は変換結果を格納しない。
  inline auto c16_to_c32(char16_t const* c16, std::size_t n, char32_t* c32)
    -> std::size_t
  {
    if (c16 == nullptr)
      return 0;

    char16_t h = u'\0';
    char16_t l = u'\0';

    if (n > 0)
      h = c16[0];
    if (n > 1)
      l = c16[1];

    if (n > 1 && 0xd800 <= h && h <= 0xdbff)
    {
      if (0xdc00 <= l && l <= 0xdfff)
      {
        if (c32 != nullptr)
          *c32 = static_cast<char32_t>(0x10000 + (h - 0xd800) * 0x400 + (l - 0xdc00));
        n = 2;
      }
    }
    else if (h < 0xdc00 || 0xdfff < h)
    {
      if (c32 != nullptr)
        *c32 = static_cast<char32_t>(h);
      n = 1;
    }
    else
    {
      n = 0;
    }
    return n;
  }

  /// char16_tからchar32_tへの変換
  /// @param[in]  c16   char16_t型の文字
  /// @return     char32_t型の文字を返す。変換に失敗した場合はナル文字を返す。
  /// サロゲートペアには対応しない。
  inline auto c16_to_c32(char16_t c16)
  {
    if ((0xd800 <= c16 && c16 <= 0xdbff) && (0xdc00 <= c16 && c16 <= 0xdfff))
      return U'\0';
    return static_cast<char32_t>(c16);
  }

  /// char8_tからchar32_tへの変換
  /// @param[in]  c8    char8_t型の文字配列
  /// @param[in]  n     c8が指す配列の要素数
  /// @param[out] c32   変換したchar32_t文字の格納先
  /// @return     c16配列の解析した要素数を返す。
  /// c32がnullptrの場合は変換結果を格納しない。
  inline auto c8_to_c32(char8_t const* c8, std::size_t n, char32_t* c32)
    -> std::size_t
  {
    if (c8 == nullptr)
      return 0;

    if (n > 0 && c8[0] <= 0x7f)
    {
      if (c32 != nullptr)
        *c32 = static_cast<char32_t>(c8[0]);
      n = 1;
    }
    else if (n > 1 && ((c8[0] & 0b1110'0000) == 0b1100'0000))
    {
      if ((c8[1] & 0b1100'0000) == 0b1000'0000)
      {
        if (c32 != nullptr)
          *c32 = (c8[0] & 0b0001'1111) << 6 | (c8[1] & 0b0011'1111);
        n = 2;
      }
    }
    else if (n > 1 && (c8[0] & 0b1111'0000) == 0b1110'0000)
    {
      if (((c8[1] & 0b1100'0000) == 0b1000'0000) && ((c8[2] & 0b1100'0000) == 0b1000'0000))
      {
        if (c32 != nullptr)
          *c32 = (c8[0] & 0b0000'1111) << 12 | (c8[1] & 0b0011'1111) << 6 | (c8[2] & 0b0011'1111);
        n = 3;
      }
    }
    else if (n > 2 && (c8[0] & 0b1111'1000) == 0b1111'0000)
    {
      if (((c8[1] & 0b1100'0000) == 0b1000'0000) && ((c8[2] & 0b1100'0000) == 0b1000'0000) && ((c8[3] & 0b1100'0000) == 0b1000'0000))
      {
        if (c32 != nullptr)
          *c32 = (c8[0] & 0b0000'1111) << 18 | (c8[1] & 0b0011'1111) << 12 | (c8[2] & 0b0011'1111) << 6 | (c8[3] & 0b0011'1111);
        n = 4;
      }
    }
    else
    {
      n = 0;
    }
    return n;
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

  /// char16_tからchar8_tへの変換
  /// @param[in]  c16   char16_t型の文字
  /// @param[in]  n1    c16が指す配列の要素数
  /// @param[out] c8    char8_t文字の格納先配列
  /// @param[in]  n2    c8が指す配列の要素数
  /// @return     c16を解析した要素数とc8に格納した要素数をpairとして返す。
  inline auto c16_to_c8(char16_t const* c16, std::size_t n1, char8_t* c8, std::size_t n2)
    -> std::pair<std::size_t, std::size_t>
  {
    char32_t c32 = 0;
    n1 = c16_to_c32(c16, n1, &c32);
    if (n1 > 0)
      n2 = c32_to_c8(c32, c8, n2);
    else
      n2 = 0;
    return { n1, n2 };
  }

  /// char8_tからchar16_tへの変換
  /// @param[in]  c8    char8_t型の文字
  /// @param[in]  n1    c8が指す配列の要素数
  /// @param[out] c16   char16_t文字の格納先配列
  /// @param[in]  n2    c16が指す配列の要素数
  /// @return     c8を解析した要素数とc16に格納した要素数をpairとして返す。
  inline auto c8_to_c16(char8_t const* c8, std::size_t n1, char16_t* c16, std::size_t n2)
    -> std::pair<std::size_t, std::size_t>
  {
    char32_t c32 = 0;
    n1 = c8_to_c32(c8, n1, &c32);
    if (n1 > 0)
      n2 = c32_to_c16(c32, c16, n2);
    else
      n2 = 0;
    return { n1, n2 };
  }
}

#endif  // !MENON_BITS_UNICODE_HH_
