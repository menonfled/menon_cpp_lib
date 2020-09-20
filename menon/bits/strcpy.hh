﻿/// @file   menon/bits/strcpy.hh
/// strcpy系関数の定義
/// @author @menofled
#ifndef MENON_BITS_STRCPY_HH_
#define MENON_BITS_STRCPY_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <algorithm>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    auto strcpy_helper(Char* s, std::size_t n, std::basic_string_view<Char, Traits> sv)
    {
      if (n == 0)
        return s;
      if (s == nullptr)
        throw std::invalid_argument("menon::strcpy");

      if (n > sv.size() + 1)
        n = sv.size() + 1;
      std::copy_n(sv.cbegin(), n - 1, s);
      s[n - 1] = {};
      return s;
    }
  }

  /// 文字列のコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  n     s1が指す配列の要素数
  /// @param[in]  s2    コピー元の文字列
  /// @return     s1を返す。
  /// nが1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, typename String>
  inline auto strcpy(Char* s1, std::size_t n, String const& s2)
  {
    using ::menon::sv;
    return detail::strcpy_helper(s1, n, sv(s2));
  }

  /// 文字列のコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  s2    コピー元の文字列
  /// @return     s1を返す。
  /// s1が1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, std::size_t N, typename String>
  inline auto strcpy(Char (&s1)[N], String const& s2)
  {
    using ::menon::sv;
    return detail::strcpy_helper(s1, N, sv(s2));
  }

  /// 文字列のコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  s2    コピー元の文字列
  /// @return     s1を返す。
  template <typename Char, typename Traits, typename Allocator, typename String>
  inline auto strcpy(std::basic_string<Char, Traits, Allocator>& s1, String const& s2)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    using ::menon::sv;
    auto t = sv(s2);
    s1.assign(t.cbegin(), t.cend());
    return s1;
  }
}

#endif  // !MENON_BITS_STRCPY_HH_
