/// @file   menon/bits/fill.hh
/// fill系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_FILL_HH_
#define MENON_BITS_FILL_HH_
#pragma once

#include "menon/bits/config.hh"
#include <algorithm>
#include <iterator>
#include <array>
#include <bitset>

namespace menon
{
  /// 列コンテナの全要素を同じ値で埋める。
  /// @param[in]  container     列コンテナ
  /// @param[in]  value         埋める値
  /// @return     無し
  template <typename C>
  inline void fill(C& container, typename C::value_type const& value)
  {
    std::fill(std::begin(container), std::end(container), value);
  }

  /// 配列の全要素を同じ値で埋める。
  /// @param[in]  container     列コンテナ
  /// @param[in]  value         埋める値
  /// @return     無し
  template <typename T, std::size_t N>
  inline void fill(T (&array)[N], T const& value)
  {
    std::fill(std::begin(array), std::end(array), value);
  }

  /// arrayの全要素を同じ値で埋める。
  /// @param[in]  container     列コンテナ
  /// @param[in]  value         埋める値
  /// @return     無し
  template <typename T, std::size_t N>
  inline void fill(std::array<T, N>& array, T const& value)
  {
    array.fill(value);
  }

  /// bitsetの全要素を同じ値で埋める。
  /// @param[in]  container     列コンテナ
  /// @param[in]  value         埋める値
  /// @return     無し
  template <std::size_t N>
  inline void fill(std::bitset<N>& bs, bool value)
  {
    if (value)
      bs.set();
    else
      bs.reset();
  }
}

#endif  // !MENON_BITS_FILL_HH_
