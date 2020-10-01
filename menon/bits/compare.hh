/// @file   menon/bits/compare.hh
/// 比較関数の定義
/// @author @menonfled
#ifndef MENON_BITS_COMPARE_HH_
#define MENON_BITS_COMPARE_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <concepts>
#include <type_traits>

namespace menon
{
  namespace detail
  {
    template <std::integral T, std::integral U>
    constexpr bool lt_helper(T lhs, U rhs)
    {
      return lhs < rhs;
    }

    template <std::signed_integral T, std::unsigned_integral U>
    constexpr bool lt_helper(T lhs, U rhs)
    {
      if (lhs < 0)
        return true;
      using type = decltype(lhs + rhs);
      return static_cast<type>(lhs) < static_cast<type>(rhs);
    }

    template <std::unsigned_integral T, std::signed_integral U>
    constexpr bool lt_helper(T lhs, U rhs)
    {
      if (rhs < 0)
        return false;
      using type = decltype(lhs + rhs);
      return static_cast<type>(lhs) < static_cast<type>(rhs);
    }
  }

  /// 整数の比較（左辺 < 右辺）
  /// @param[in]  lhs     左辺
  /// @param[in]  rhs     右辺
  /// lhs < rhsの場合はtrueを、それ以外はfalseを返す。
  template <std::integral T, std::integral U>
  constexpr bool lt(T lhs, U rhs)
  {
    return detail::lt_helper(+lhs, +rhs);
  }

  /// 浮動小数点数の比較（左辺 < 右辺）
  /// @param[in]  lhs     左辺
  /// @param[in]  rhs     右辺
  /// lhs < rhsの場合はtrueを、それ以外はfalseを返す。
  template <std::floating_point T>
  constexpr bool lt(T lhs, T rhs)
  {
    return lhs < rhs;
  }
}

#endif  // !MENON_BITS_COMPARE_HH_




