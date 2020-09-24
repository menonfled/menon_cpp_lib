/// @file   menon/bits/toctrans.hh
/// 文字種変換関数の定義
/// @author @menonfled
#ifndef MENON_BITS_TOCTRANS_HH_
#define MENON_BITS_TOCTRANS_HH_
#pragma once

#include "menon/bits/sv.hh"
#include "menon/bits/isctype.hh"
#include <string>
#include <algorithm>
#include <iterator>

namespace menon
{
  /// 変換種別
  using ctrans_t = char (*)(char);

  /// 小文字への変換
  /// @param[in]  c     変換対象の文字
  /// @return     cが大文字の場合は対応する小文字を、それ以外はcを返す。
  template <typename Char>
  constexpr Char tolower(Char c)
  {
    if (isupper(c))
      return static_cast<Char>(c | 0x20);
    return c;
  }

  /// 大文字への変換
  /// @param[in]  c     変換対象の文字
  /// @return     cが小文字の場合は対応する大文字を、それ以外はcを返す。
  template <typename Char>
  constexpr Char toupper(Char c)
  {
    if (islower(c))
      return static_cast<Char>(c & ~0x20);
    return c;
  }

  /// 指定した種別による変換
  /// @param[in]  c     変換対象の文字
  /// @param[in]  trans 変換種別
  /// @return     transで指定した文字種にcを変換した結果を返す。
  template <typename Char>
  constexpr Char toctrans(Char c, ctrans_t trans)
  {
    if (trans == tolower<char>)
      c = tolower(c);
    else if (trans == toupper<char>)
      c = toupper(c);
    return c;
  }

  /// 文字列から変換種別への変換
  /// @param[in]  name    変換種別に対応する文字列
  /// @return     nameに対応する変換種別を返す。
  constexpr ctrans_t ctrans(std::string_view name)
  {
    if (name == "tolower")
      return tolower;
    if (name == "toupper")
      return toupper;
    return {};
  }

  /// 文字列を小文字に変換する。
  /// @param[in]  s     変換対象の文字列
  /// @return     sに含まれる'A'～'Z'を'a'～'z'に変換した文字列を返す。
  template <typename String>
  auto strtolower(String const& s)
  {
    using ::menon::sv;
    auto t = sv(s);
    using sv_type = decltype(t);
    using char_type = typename sv_type::value_type;
    std::basic_string<char_type> r;
    r.reserve(t.size());
    std::transform(t.cbegin(), t.cend(), std::back_inserter(r), &menon::tolower<char_type>);
    return r;
  }

  /// 文字列を大文字に変換する。
  /// @param[in]  s     変換対象の文字列
  /// @return     sに含まれる'a'～'z'を'A'～'Z'に変換した文字列を返す。
  template <typename String>
  auto strtoupper(String const& s)
  {
    using ::menon::sv;
    auto t = sv(s);
    using sv_type = decltype(t);
    using char_type = typename sv_type::value_type;
    std::basic_string<char_type> r;
    r.reserve(t.size());
    std::transform(t.cbegin(), t.cend(), std::back_inserter(r), &menon::toupper<char_type>);
    return r;
  }
}

#endif  // !MENON_BITS_TOCTRANS_HH_
