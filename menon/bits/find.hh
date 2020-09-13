#ifndef MENON_BITS_FIND_HH_
#define MENON_BITS_FIND_HH_
#pragma once

#include "menon/bits/config.hh"
#include <algorithm>

namespace menon
{
  /// 列から値を探索する。
  /// @param[in]  c     列コンテナ
  /// @param[in]  value 探索する値
  /// @return     cの要素にvalueに一致する要素があればその要素へのポインタを返す。なければnullptrを返す。
  template <typename C>
  inline auto find(C& c, typename C::value_type value)
    -> decltype(&*c.begin())
  {
    auto it = std::find(c.begin(), c.end(), value);
    if (it != c.end())
      return &*it;
    return nullptr;
  }

  /// 列から値を探索する。
  /// @param[in]  c     列コンテナ
  /// @param[in]  value 探索する値
  /// @return     cの要素にvalueに一致する要素があればその要素へのポインタを返す。なければnullptrを返す。
  /// find関数との違いは、cfind関数はC::const_pointerを返すことである。
  template <typename C>
  inline auto cfind(C& c, typename C::value_type value)
    -> typename C::const_pointer
  {
    auto it = std::find(c.cbegin(), c.cend(), value);
    if (it != c.cend())
      return &*it;
    return nullptr;
  }




}

#endif  // !MENON_BITS_FIND_HH_
