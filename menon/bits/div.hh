/// @file   menon/bits/div.hh
/// div系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_DIV_HH_
#define MENON_BITS_DIV_HH_
#pragma once

#include "menon/bits/abs.hh"
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

  /// udiv関数の結果
  template <typename T>
  struct udiv_t
  {
    T quot; ///< 商の絶対値
    T rem;  ///< 剰余の絶対値
    bool quot_sign; ///< 商の符号
    bool rem_sign;  ///< 剰余の符号
  };

  namespace detail
  {
    template <std::unsigned_integral T>
    constexpr auto udiv_helper(T numer, T denom)
      -> udiv_t<T>
    {
      if (denom == 0)
        throw std::invalid_argument("menon::udiv");
      return { numer / denom, numer % denom, false, false };
    }

    template <std::signed_integral T>
    constexpr auto udiv_helper(T numer, T denom)
      -> udiv_t<std::make_unsigned_t<T>>
    {
      if (denom == 0)
        throw std::invalid_argument("menon::udiv");
      auto u_numer = uabs(numer);
      auto u_denom = uabs(denom);
      bool sign_quot = (numer < 0) != (denom < 0); 
      return { u_numer / u_denom, u_numer % u_denom, sign_quot, sign_quot && (numer < 0) };
    }

    template <std::floating_point T>
    auto floating_udiv_helper(T numer, T denom)
      -> udiv_t<T>
    {
      using value_type = decltype(numer / denom);
      if (denom == 0 && numer != 0)
        throw std::invalid_argument("menon::div");
      value_type quot;
      value_type rem;
      std::modf(numer / denom, &quot);
      rem = std::fmod(numer, denom);
      return { std::abs(quot), std::abs(rem), quot < 0, rem < 0 };
    }
  }

  /// 整数除算における商と剰余
  /// @param[in]  numer   被除数
  /// @param[in]  denom   除数
  /// @return     numer÷denomの商と剰余をdiv_t型で返す。
  /// @throw      remが0の場合、invalid_argument例外を送出する。
  /// @throw      quot/remが符号付き整数型であり、quotが型の最小値かつremが-1の場合、out_of_range例外を送出する。
  /// @throw      結果の商または値を表現できない場合はout_of_range例外を送出する。
  template <std::integral T, std::integral U>
  constexpr auto div(T numer, U denom)
    -> div_t<decltype(numer / denom)>
  {
    using value_type = decltype(numer / denom);
    if (denom == 0)
      throw std::invalid_argument("menon::div");
    if constexpr (std::is_signed_v<value_type>)
    {
      if (numer == std::numeric_limits<value_type>::min() && denom == -1)
        throw std::out_of_range("menon::div");
    }
    else
    {
      // 商または剰余を表現できない場合はout_of_range例外を送出
      if constexpr (std::is_signed_v<T>)
      {
        if (numer < 0)
          throw std::out_of_range("menon::div");
      }
      else if constexpr (std::is_signed_v<U>)
      {
        if (denom < 0)
          throw std::out_of_range("menon::div");
      }
    }
    return { numer / denom, numer % denom };
  }

  /// 浮動小数点除算における商と剰余
  /// @param[in]  numer   被除数
  /// @param[in]  denom   除数
  /// @return     numer÷denomの商と剰余をdiv_t型で返す。
  /// @throw      remが0の場合、invalid_argument例外を送出する。
  template <typename T, typename U>
  auto div(T numer, U denom)
  {
    static_assert(std::numeric_limits<T>::is_specialized);
    static_assert(std::numeric_limits<U>::is_specialized);

    using value_type = decltype(numer / denom);
    if (denom == 0 && numer != 0)
      throw std::invalid_argument("menon::div");
    div_t<value_type> r;
    std::modf(numer / denom, &r.quot);
    r.rem = std::fmod(numer, denom);
    return r;
  }

  /// オーバーフローが発生しない除算における商と剰余
  /// @param[in]  numer   被除数
  /// @param[in]  denom   除数
  /// @return     numer÷denomの商と剰余をudiv_t型で返す。
  /// @throw      remが0の場合、invalid_argument例外を送出する。
  template <typename T, typename U>
  constexpr auto udiv(T numer, U denom)
  {
    using value_type = decltype(numer / denom);
    if constexpr (std::is_floating_point_v<value_type>)
      return detail::floating_udiv_helper(static_cast<value_type>(numer), static_cast<value_type>(denom));
    else
      return detail::udiv_helper(static_cast<value_type>(numer), static_cast<value_type>(denom));
  }
}

#endif  // !MENON_BITS_DIV_HH_
