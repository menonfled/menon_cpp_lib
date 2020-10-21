/// @file   menon/bits/starts_with.hh
/// starts_with系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STARTS_WITH_HH_
#define MENON_BITS_STARTS_WITH_HH_
#pragma once

#include "menon/bits/sv.hh"

namespace menon
{
  /// 指定の文字列で始まるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字列
  /// @return       sがxで始まる場合はtrueを、そうでなければfalseを返す。
  template <sv_like String1, sv_like String2>
  constexpr bool starts_with(String1 const& s, String2 const& x)
  {
    using menon::sv;
    return sv(s).starts_with(sv(x));
  }

  /// 指定の文字で始まるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字
  /// @return       sがxで始まる場合はtrueを、そうでなければfalseを返す。
  template <sv_like String>
  constexpr bool starts_with(String const& s, typename String::value_type x)
  {
    using menon::sv;
    return sv(s).starts_with(x);
  }

  /// 指定の文字列で終わるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字列
  /// @return       sがxで終わる場合はtrueを、そうでなければfalseを返す。
  template <sv_like String1, sv_like String2>
  constexpr bool ends_with(String1 const& s, String2 const& x)
  {
    using menon::sv;
    return sv(s).ends_with(sv(x));
  }

  /// 指定の文字で終わるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字
  /// @return       sがxで終わる場合はtrueを、そうでなければfalseを返す。
  template <sv_like String>
  constexpr bool ends_with(String const& s, typename String::value_type x)
  {
    using menon::sv;
    return sv(s).ends_with(x);
  }

  /// 指定の文字列で始まるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字列
  /// @return       sがxで始まる場合はtrueを、そうでなければfalseを返す。
  /// starts_with関数の別名
  template <sv_like String1, sv_like String2>
  constexpr bool start_with(String1 const& s, String2 const& x)
  {
    return starts_with(s, x);
  }

  /// 指定の文字で始まるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字
  /// @return       sがxで始まる場合はtrueを、そうでなければfalseを返す。
  /// starts_with関数の別名
  template <sv_like String>
  constexpr bool start_with(String const& s, typename String::value_type x)
  {
    return starts_with(s, x);
  }

  /// 指定の文字列で終わるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字列
  /// @return       sがxで終わる場合はtrueを、そうでなければfalseを返す。
  /// ends_with関数の別名
  template <sv_like String1, sv_like String2>
  constexpr bool end_with(String1 const& s, String2 const& x)
  {
    return ends_with(s, x);
  }

  /// 指定の文字で終わるかの判定
  /// @param[in]    s     判定対象の文字列
  /// @param[in]    x     指定の文字
  /// @return       sがxで終わる場合はtrueを、そうでなければfalseを返す。
  /// ends_with関数の別名
  template <sv_like String>
  constexpr bool end_with(String const& s, typename String::value_type x)
  {
    return ends_with(s, x);
  }
}

#endif  // !MENON_BITS_STARTS_WITH_HH_
