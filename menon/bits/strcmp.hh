﻿/// @file   menon/bits/strcmp.hh
/// @author @menonfled
/// strcmp系関数の定義
#ifndef MENON_BITS_STRCMP_HH_
#define MENON_BITS_STRCMP_HH_
#pragma once

#include "menon/bits/sv.hh"

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    constexpr auto strcmp_helper(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2)
    {
      return sv1.compare(sv2);
    }

    template <typename Char, typename Traits>
    constexpr auto strncmp_helper(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2, std::size_t n)
    {
      return sv1.compare(0, n, sv2, 0, n);
    }
  }

  /// 文字列の比較
  /// @param[in]  s1  比較対象の文字列
  /// @param[in]  s2  比較対象の文字列
  /// @retuen     s1 < s2のときは負、s1 == s2のときは0、s1 > s2のときは正の値を返す。
  template <typename T, typename U>
  constexpr auto strcmp(T const& s1, U const& s2)
  {
    using menon::sv;
    return detail::strcmp_helper(sv(s1), sv(s2));
  }

  /// 指定文字数だけ文字列を比較
  /// @param[in]  s1  比較対象の文字列
  /// @param[in]  s2  比較対象の文字列
  /// @param[in]  n   指定文字数
  /// @retuen     s1 < s2のときは負、s1 == s2のときは0、s1 > s2のときは正の値を返す。
  template <typename T, typename U>
  constexpr auto strncmp(T const& s1, U const& s2, std::size_t n)
  {
    using menon::sv;
    return detail::strncmp_helper(sv(s1), sv(s2), n);
  }
}

#endif  // !MENON_BITS_STRCMP_HH_
