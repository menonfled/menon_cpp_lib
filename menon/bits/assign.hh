/// @file   menon/bits/assign.hh
/// assign系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_ASSIGN_HH_
#define MENON_BITS_ASSIGN_HH_
#pragma once

#include "menon/bits/swap.hh"
#include "menon/bits/reserve.hh"
#include <concepts>
#include <algorithm>
#include <iterator>
#include <utility>

namespace menon
{
  /// オブジェクトの代入
  /// @param[in]    src     代入元のオブジェクト
  /// @param[in]    dest    代入先のオブジェクト
  /// @return       無し
  template <typename From, typename To> requires std::assignable_from<To, From>
  inline auto assign(From&& src, To& dest)
  {
    dest = std::forward<From>(src);
  }

  /// オブジェクトの代入
  /// @param[in]    src     代入元のオブジェクト
  /// @param[in]    dest    代入先のオブジェクト
  /// @return       無し
  template <typename From, typename To>
  inline auto assign(From const& src, To& dest)
  {
    To t;
    reserve(t, std::size(src));
    std::copy(std::cbegin(src), std::cend(src), std::back_inserter(t));
    swap(dest, t);
  }
}

#endif  // !MENON_BITS_ASSIGN_HH_
