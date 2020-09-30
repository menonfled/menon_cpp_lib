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
    template <typename T, typename U>
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

  /// 算術型の比較（左辺 < 右辺）
  /// @param[in]  lhs     左辺
  /// @param[in]  rhs     右辺
  /// lhs < rhsの場合はtrueを、それ以外はfalseを返す。
  template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
  constexpr bool lt(T lhs, U rhs)
  {
    return detail::lt_helper(+lhs, +rhs);
  }

  /// 文字列の比較（左辺 < 右辺）
  /// @param[in]  lhs     左辺
  /// @param[in]  rhs     右辺
  /// lhs < rhsの場合はtrueを、それ以外はfalseを返す。
  template <sv_like T, sv_like U>
  constexpr bool lt(T const& lhs, T const& rhs)
  {
    using ::menon::sv;
    return sv(lhs) < sv(rhs);
  }

  /// 一般的なオブジェクトの比較（左辺 < 右辺）
  /// @param[in]  lhs     左辺
  /// @param[in]  rhs     右辺
  /// lhs < rhsの場合はtrueを、それ以外はfalseを返す。
  template <typename T>
  constexpr bool lt(T const& lhs, T const& rhs)
  {
    return lhs < rhs;
  }
}

#endif  // !MENON_BITS_COMPARE_HH_




