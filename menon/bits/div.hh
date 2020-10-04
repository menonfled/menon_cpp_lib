/// @file   menon/bits/div.hh
/// div系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_DIV_HH_
#define MENON_BITS_DIV_HH_
#pragma once

#include "menon/bits/config.hh"
#include <cmath>
#include <concepts>
#include <limits>
#include <type_traits>

namespace menon
{
  /// div関数の結果
  template <typename T>
  struct div_t
  {
    T quot; ///< 商
    T rem;  ///< 剰余
  };

  /// 整数除算における商と剰余
  /// @param[in]  numer   被除数
  /// @param[in]  denom   除数
  /// @return     numer÷denomの商と剰余をdiv_t型で返す。
  /// @throw      remが0の場合、invalid_argument例外を送出する。
  /// @throw      quot/remが符号付き整数型であり、quotが型の最小値かつremが-1の場合、out_of_range例外を送出する。
  template <std::integral T, std::integral U>
  constexpr auto div(T numer, U denom)
  {
    using value_type = decltype(numer / denom);
    if (denom == 0)
      throw std::invalid_argument("menon::div");
    if constexpr (std::is_signed_v<value_type>)
      if (numer == std::numeric_limits<value_type>::min() && denom == -1)
        throw std::out_of_range("menon::div");
    div_t<value_type> r { numer / denom, numer % denom };
    return r;
  }

  /// 浮動小数点除算における商と剰余
  /// @param[in]  numer   被除数
  /// @param[in]  denom   除数
  /// @return     numer÷denomの商と剰余をdiv_t型で返す。
  /// @throw      remが0の場合、invalid_argument例外を送出する。
  template <typename T, typename U>
  auto div(T numer, U denom)
  {
    static_assert(std::is_arithmetic_v<T>);
    static_assert(std::is_arithmetic_v<U>);

    using value_type = decltype(numer / denom);
    if (denom == 0 && numer != 0)
      throw std::invalid_argument("menon::div");
    div_t<value_type> r;
    std::modf(numer / denom, &r.quot);
    r.rem = std::fmod(numer, denom);
    return r;
  }
}

#endif  // !MENON_BITS_DIV_HH_
