/// @file   menon/bits/abs.hh
/// abs系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_ABS_HH_
#define MENON_BITS_ABS_HH_
#pragma once

#include "menon/bits/config.hh"
#include <type_traits>
#include <limits>
#include <stdexcept>
#include <concepts>

namespace menon
{
  /// 符号付き整数の絶対値
  /// @param[in]  value     絶対値を求める値
  /// @return     valueの絶対値を整数拡張した型として返す。
  /// @throw      valueの絶対を表現できない場合はout_of_range例外を送出する。
  template <std::signed_integral T>
  constexpr auto abs(T value)
  {
    auto t = +value;
    if (t == std::numeric_limits<decltype(t)>::min())
      throw std::out_of_range("menon::abs");
    return t < 0 ? -t : +t;
  }

  /// 符号無し整数の絶対値
  /// @param[in]  value     絶対値を求める値
  /// @return     valueを整数拡張した型として返す。
  template <std::unsigned_integral T>
  constexpr auto abs(T value)
  {
    return +value;
  }

  /// 浮動小数点数の絶対値
  /// @param[in]  value     絶対値を求める値
  /// @return     valueの絶対値を返す。
  template <std::floating_point T>
  constexpr auto abs(T value)
  {
    return value < 0 ? -value : +value;
  }
}

#endif  // !MENON_BITS_ABS_HH_
