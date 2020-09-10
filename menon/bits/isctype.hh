/// @file   menon/bits/isctype.hh
/// author  @menonfled
/// 文字種判別関数の定義
///
/// このヘッダーファイルで定義する関数は下記を除きCの同名の関数と同様に機能する。
///
/// - 文字型を問わない
/// - 文字の0x00～0x7fについてのみ判定を行い、それ以外はfalseを返す
/// - ロケールに関係なくCロケールと同様に判定を行う
/// - 結果をintではなくboolで返す
#ifndef MENON_BITS_ISCTYPE_HH_
#define MENON_BITS_ISCTYPE_HH_
#pragma once

#include "menon/bits/config.hh"
#include <type_traits>
#include <string_view>
#include <cctype>
#include <cwctype>
#include <cstddef>
#include <cstdint>

namespace menon
{
  namespace detail
  {
    constexpr std::uint16_t ctype[] =
    {
      0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
      0x0001, 0x0109, 0x0009, 0x0009, 0x0009, 0x0009, 0x0001, 0x0001,
      0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
      0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
      0x0018, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
      0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
      0x0682, 0x0682, 0x0282, 0x0282, 0x0282, 0x0282, 0x0282, 0x0282,
      0x0082, 0x0082, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
      0x0004, 0x00c0, 0x00c0, 0x00c0, 0x00c0, 0x00c0, 0x00c0, 0x0040,
      0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040,
      0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040,
      0x0040, 0x0040, 0x0040, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004,
      0x0004, 0x00a0, 0x00a0, 0x00a0, 0x00a0, 0x00a0, 0x00a0, 0x0020,
      0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
      0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
      0x0020, 0x0020, 0x0020, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001,
   };
  }

  /// 文字種型
  enum ctype_t
  {
    cntrl  = 0x0001,
    digit  = 0x0002,
    punct  = 0x0004,
    space  = 0x0008,
    blank  = 0x0110,
    lower  = 0x0020,
    upper  = 0x0040,
    alnum  = 0x0062,
    alpha  = 0x0060,
    graph  = 0x0066,
    print  = 0x0076,
    xdigit = 0x0080,
    octal  = 0x0200,
    binary = 0x0400,
  };

  /// 文字列から文字種への変換
  /// @param[in]  name    文字種を表す文字列
  /// @return     nameに対応する文字種を返す。
  constexpr ctype_t ctype(std::string_view name)
  {
    if (name == "cntrl")
      return cntrl;
    if (name == "digit")
      return digit;
    if (name == "punct")
      return punct;
    if (name == "space")
      return space;
    if (name == "blank")
      return blank;
    if (name == "lower")
      return lower;
    if (name == "upper")
      return upper;
    if (name == "alnum")
      return alnum;
    if (name == "alpha")
      return alpha;
    if (name == "graph")
      return graph;
    if (name == "print")
      return print;
    if (name == "xdigit")
      return xdigit;
    if (name == "octal")
      return octal;
    if (name == "binary")
      return binary;
    return {};
  }

  /// 文字種の判別
  /// @param[in]  c     文字
  /// @param[in]  type  文字種
  /// @return     cがtypeで指定した文字種の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isctype(Char c, ctype_t type)
  {
    if ((c & 0x7f) != c)
      return false;
    return detail::ctype[static_cast<std::size_t>(c)] & type;
  }

  /// 制御文字の判別
  /// @param[in]  c     文字
  /// @return     cが制御文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool iscntrl(Char c)
  {
    return isctype(c, cntrl);
  }

  /// 数字の判別
  /// @param[in]  c     文字
  /// @return     cが数字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isdigit(Char c)
  {
    return isctype(c, digit);
  }

  /// 区切り文字の判別
  /// @param[in]  c     文字
  /// @return     cが区切り文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool ispunct(Char c)
  {
    return isctype(c, punct);
  }

  /// 空白類文字の判別
  /// @param[in]  c     文字
  /// @return     cが空白類文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isspace(Char c)
  {
    return isctype(c, space);
  }

  /// 空白または水平タブの判別
  /// @param[in]  c     文字
  /// @return     cが空白または水平タブの場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isblank(Char c)
  {
    return isctype(c, blank);
  }

  /// 小文字の判別
  /// @param[in]  c     文字
  /// @return     cが小文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool islower(Char c)
  {
    return isctype(c, lower);
  }

  /// 大文字の判別
  /// @param[in]  c     文字
  /// @return     cが大文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isupper(Char c)
  {
    return isctype(c, upper);
  }

  /// 英数字の判別
  /// @param[in]  c     文字
  /// @return     cが英数字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isalnum(Char c)
  {
    return isctype(c, alnum);
  }

  /// 英字の判別
  /// @param[in]  c     文字
  /// @return     cが英字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isalpha(Char c)
  {
    return isctype(c, alpha);
  }

  /// 図形文字の判別
  /// @param[in]  c     文字
  /// @return     cが図形文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isgraph(Char c)
  {
    return isctype(c, graph);
  }

  /// 印字可能文字の判別
  /// @param[in]  c     文字
  /// @return     cが印字可能文字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isprint(Char c)
  {
    return isctype(c, print);
  }

  /// 十六進数字の判別
  /// @param[in]  c     文字
  /// @return     cが十六進数字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isxdigit(Char c)
  {
    return isctype(c, xdigit);
  }

  /// 八進数字の判別
  /// @param[in]  c     文字
  /// @return     cが八進数字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isoctal(Char c)
  {
    return isctype(c, octal);
  }

  /// 二進数字の判別
  /// @param[in]  c     文字
  /// @return     cが二進数字の場合はtrueを、それ以外はfalseを返す。
  template <typename Char>
  constexpr bool isbinary(Char c)
  {
    return isctype(c, binary);
  }
}

#endif  // !MENON_BITS_ISCTYPE_HH_
