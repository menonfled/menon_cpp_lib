/// @file   menon/bits/swap.hh
/// swap関数の定義
/// @author @menonfled
#ifndef MENON_BITS_SWAP_HH_
#define MENON_BITS_SWAP_HH_
#pragma once

#include "menon/bits/config.hh"
#include <utility>

namespace menon
{
  namespace detail
  {
    // swapメンバ関数の有無判定用コンセプト
    template <typename T>
    concept has_swap = requires (T& a, T& b)
    {
      a.swap(b);
    };
  }

  /// 値の交換
  /// @param[in,out]  a     値を交換するオブジェクト  
  /// @param[in,out]  b     値を交換するオブジェクト  
  template <typename T>
  inline auto swap(T& a, T& b) noexcept
  {
    using ::std::swap;
    swap(a, b);
  }

  /// 値の交換
  /// @param[in,out]  a     値を交換するオブジェクト  
  /// @param[in,out]  b     値を交換するオブジェクト  
  /// aおよびbの型がswapメンバ関数を持つ場合に適用される。
  template <detail::has_swap T>
  inline auto swap(T& a, T& b) noexcept
  {
    a.swap(b);
  }
}

#endif  // !MENON_BITS_SWAP_HH_
