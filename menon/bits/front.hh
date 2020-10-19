/// @file   menon/bits/front.hh
/// front系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_FRONT_HH_
#define MENON_BITS_FRONT_HH_
#pragma once

#include "menon/bits/config.hh"
#include <cstddef>

namespace menon
{
  /// 先頭要素へのポインタ
  /// @param[in]  container     列コンテナ
  /// @return     containerが空でなければ先頭要素へのポインタを、空の場合はnullptrを返す。
  template <typename C>
  constexpr auto front(C const& container)
    -> typename C::const_pointer
  {
    if (container.empty())
      return nullptr;
    return &container.front();
  }

  /// 先頭要素へのポインタ
  /// @param[in]  array         配列
  /// @return     配列の先頭要素へのポインタを返す。
  template <typename T, std::size_t N>
  constexpr auto front(T const (&array)[N])
    -> T const*
  {
    static_assert(N > 0);
    return &array[0];
  }
}

#endif  // !MENON_BITS_FRONT_HH_
