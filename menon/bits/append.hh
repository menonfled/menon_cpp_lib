/// @file   menon/bits/append.hh
/// append系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_APPEND_HH_
#define MENON_BITS_APPEND_HH_
#pragma once

#include "menon/bits/assign.hh"

namespace menon
{
  /// オブジェクトの追加
  /// @param[in]    src     追加元のオブジェクト
  /// @param[in]    dest    追加先のオブジェクト
  /// @return       無し
  template <typename From, typename To>
  inline auto append(From const& src, To& dest)
  {
    To t;
    reserve(t, std::size(dest) + std::size(src));
    assign(dest, t);
    std::copy(std::cbegin(src), std::cend(src), std::back_inserter(t));
    swap(dest, t);
  }
}

#endif  // !MENON_BITS_APPEND_HH_
