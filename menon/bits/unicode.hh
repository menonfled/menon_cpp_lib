/// @file   menon/bits/unicode.hh
/// @author @menonfled
/// Unicode関連処理の宣言・定義
#ifndef MENON_BITS_UNICODE_HH_
#define MENON_BITS_UNICODE_HH_
#pragma once

#include "menon/bits/config.hh"
#include <array>

namespace menon
{
  /// char32_tからchar16_tへの変換
  /// @param[in]  c32   char32_t型の文字
  /// @return     char16_t型の文字を返す。
  /// サロゲートペアを考慮し、結果は2要素のarrayとして返す。
  /// 不要な要素にはナル文字を格納する。
  constexpr auto c32_to_c16(char32_t c32)
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

  /// char16_tからchar32_tへの変換
  /// @param[in]  c16   char16_t型の文字
  /// @return     char32_t型の文字を返す。変換に失敗した場合はナル文字を返す。
  /// サロゲートペアを考慮し、引数は2要素の配列として受け取る。
  /// サロゲートペアではない場合は最初の1要素のみを使用し、2要素目は無視する。
  constexpr auto c16_to_c32(std::array<char16_t, 2> const& c16)
  {
    char32_t c32 = U'\0';

    auto [h, l] = c16;
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
}

#endif  // !MENON_BITS_UNICODE_HH_
