/// @file   menon/bits/reserve.hh
/// reserve関数の定義
/// @author @menonfled
#ifndef MENON_BITS_RESERVE_HH_
#define MENON_BITS_RESERVE_HH_
#pragma once

#include "menon/bits/config.hh"
#include "menon/bits/has_member.hh"
#include <stdexcept>
#include <type_traits>

#ifndef MENON_HAS_RESERVE_
#define MENON_HAS_RESERVE_
MENON_DEFINE_HAS_MEMBER(reserve)
#endif

#ifndef MENON_HAS_CLEAR_
#define MENON_HAS_CLEAR_
MENON_DEFINE_HAS_MEMBER(clear)
#endif

namespace menon
{
  /// キャパシティの予約
  /// @param[in]  container   対象のコンテナ
  /// @param[in]  size        予約するサイズ（要素数）
  /// @return     無し
  /// @throw      C::reserveメンバ関数が無い場合、containerの要素数がsizeより少なければout_of_range例外を送出する。
  /// C::reserveメンバ関数があればそれを呼び出す。
  template <typename C>
  inline auto reserve(C& container, decltype(std::size(container)) size)
  {
    if constexpr (has_reserve_v<C>)
    {
      container.reserve(size);
    }
    else if constexpr (!has_clear_v<C>)
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
