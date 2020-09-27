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
}

#endif  // !MENON_BITS_DIV_HH_
