/// @file   menon/bits/reserve.hh
/// reserve関数の定義
/// @author @menonfled
#ifndef MENON_BITS_RESERVE_HH_
#define MENON_BITS_RESERVE_HH_
#pragma once

#include "menon/bits/config.hh"
#include <stdexcept>
#include <type_traits>

namespace menon
{
  namespace detail
  {
    template<typename C>
    struct has_reserve
    {
        static std::false_type check(...);
        template<class T, int _ =(&T::reserve, 0)>
          static std::true_type  check(T*);
        static constexpr bool value = decltype(check(std::declval<C*>()))::value;
    };

    template<typename C>
    constexpr bool has_reserve_v = has_reserve<C>::value;
  }

  /// キャパシティの予約
  /// @param[in]  container   対象のコンテナ
  /// @param[in]  size        予約するサイズ（要素数）
  /// @return     無し
  /// @throw      C::reserveメンバ関数が無い場合、containerの要素数がsizeより少なければout_of_range例外を送出する。
  /// C::reserveメンバ関数があればそれを呼び出す。
  template <typename C>
  inline auto reserve(C& container, decltype(std::size(container)) size)
  {
    if constexpr (detail::has_reserve_v<C>)
    {
      container.reserve(size);
    }
    else
    {
      if (size > std::size(container))
        throw std::out_of_range("menon::reserve");
    }
  }

  /// キャパシティの予約
  /// @param[in]  array       対象の配列
  /// @param[in]  size        予約するサイズ（要素数）
  /// @return     無し
  /// @throw      arrayの要素数がsizeより少なければout_of_range例外を送出する。
  template <typename T, std::size_t N>
  inline auto reserve([[maybe_unused]] T (&array)[N], std::size_t size)
  {
      if (size > N)
        throw std::out_of_range("menon::reserve");
  }
}

#endif  // !MENON_BITS_RESERVE_HH_
