﻿/// @file   menon/bits/max.hh
/// maxおよびmin系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_MAX_HH_
#define MENON_BITS_MAX_HH_
#pragma once

#include "menon/bits/config.hh"
#include <concepts>

namespace menon
{
  /// 最大値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、大きい方の値を返す。
  /// lhsとrhsは同じ型でなければならない。
  /// @attention  std::maxと異なり、参照ではなく値を返すことに注意
  template <typename T>
  constexpr auto max(T const& lhs, T const& rhs)
  {
    return rhs < lhs ? lhs : rhs;
  }

  /// 最大値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、大きい方の値を返す。
  /// lhsとrhsはともに符号付き整数型でなければならない。
  template <std::signed_integral T, std::signed_integral U>
  constexpr auto max(T lhs, U rhs)
  {
    return rhs < lhs ? lhs : rhs;
  }

  /// 最大値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、大きい方の値を返す。
  /// lhsとrhsはともに符号無し整数型でなければならない。
  template <std::unsigned_integral T, std::unsigned_integral U>
  constexpr auto max(T lhs, U rhs)
  {
    return rhs < lhs ? lhs : rhs;
  }

  /// 最大値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、大きい方の値を返す。
  /// lhsとrhsはともに浮動小数点型でなければならない。
  template <std::floating_point T, std::floating_point U>
  constexpr auto max(T lhs, U rhs)
  {
    return rhs < lhs ? lhs : rhs;
  }

  /// 最大値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、大きい方の値を返す。
  template <std::floating_point T, std::integral U>
  constexpr auto max(T lhs, U rhs)
  {
    return rhs < lhs ? lhs : rhs;
  }

  /// 最大値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、大きい方の値を返す。
  template <std::integral T, std::floating_point U>
  constexpr auto max(T lhs, U rhs)
  {
    return rhs < lhs ? lhs : rhs;
  }

  /// 最大値
  /// @param[in]  arg0    比較する値
  /// @param[in]  args    比較する値の並び
  /// @return     引数として与えた値を比較し、最も大きい値を返す。
  template <typename T, typename... Args>
  constexpr auto max(T arg0, Args... args)
  {
    return max(arg0, max(args...));
  }

  /// 最小値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、小さい方の値を返す。
  /// lhsとrhsは同じ型でなければならない。
  /// @attention  std::maxと異なり、参照ではなく値を返すことに注意
  template <typename T>
  constexpr auto min(T const& lhs, T const rhs)
  {
    return lhs < rhs ? lhs : rhs;
  }

  /// 最小値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、小さい方の値を返す。
  /// lhsとrhsはともに符号付き整数型でなければならない。
  template <std::signed_integral T, std::signed_integral U>
  constexpr auto min(T lhs, U rhs)
  {
    return lhs < rhs ? lhs : rhs;
  }

  /// 最小値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、小さい方の値を返す。
  /// lhsとrhsはともに符号無し整数型でなければならない。
  template <std::unsigned_integral T, std::unsigned_integral U>
  constexpr auto min(T lhs, U rhs)
  {
    return lhs < rhs ? lhs : rhs;
  }

  /// 最小値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、小さい方の値を返す。
  /// lhsとrhsはともに浮動小数点型でなければならない。
  template <std::floating_point T, std::floating_point U>
  constexpr auto min(T lhs, U rhs)
  {
    return lhs < rhs ? lhs : rhs;
  }

  /// 最小値
  /// @param[in]  arg0    比較する値
  /// @param[in]  args    比較する値の並び
  /// @return     引数として与えた値を比較し、最も小さい値を返す。
  template <typename T, typename... Args>
  constexpr auto min(T arg0, Args... args)
  {
    return min(arg0, min(args...));
  }

  /// 最小値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、小さい方の値を返す。
  template <std::floating_point T, std::integral U>
  constexpr auto min(T lhs, U rhs)
  {
    return lhs < rhs ? lhs : rhs;
  }

  /// 最小値
  /// @param[in]  lhs     比較する値
  /// @param[in]  rhs     比較する値
  /// @return     lhsとrhsを比較し、小さい方の値を返す。
  template <std::integral T, std::floating_point U>
  constexpr auto min(T lhs, U rhs)
  {
    return lhs < rhs ? lhs : rhs;
  }
}

#endif  // !MENON_BITS_MAX_HH_