#ifndef MENON_BITS_FIND_HH_
#define MENON_BITS_FIND_HH_
#pragma once

#include "menon/bits/config.hh"
#include <algorithm>
#include <type_traits>

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

  /// 配列から値を探索する。
  /// @param[in]  a     配列
  /// @param[in]  value 探索する値
  /// @return     aの要素にvalueに一致する要素があればその要素へのポインタを返す。なければnullptrを返す。
  template <typename T, std::size_t N>
  inline auto find(T (&a)[N], T value)
    -> T*
  {
    auto p = std::find(a + 0, a + N, value);
    if (p != a + N)
      return p;
    return nullptr;
  }

  /// 連想コンテナから値を探索する。
  /// @param[in]  c     連想コンテナ
  /// @param[in]  key   探索するキー
  /// @return     cの要素にkeyに一致する要素があればその値へのポインタを返す。なければnullptrを返す。
  template <typename C>
  inline auto find(C& c, typename C::key_type key)
    -> decltype(&c.begin()->second)
  {
    auto it = c.find(key);
    if (it != c.end())
      return &it->second;
    return nullptr;
  }

  /// 列から値を探索する。
  /// @param[in]  c     列コンテナ
  /// @param[in]  value 探索する値
  /// @return     cの要素にvalueに一致する要素があればその要素へのポインタを返す。なければnullptrを返す。
  /// find関数との違いは、cfind関数はconst修飾されたポインタを返すことである。
  template <typename C>
  inline auto cfind(C& c, typename C::value_type value)
    -> decltype(&*c.cbegin())
  {
    auto it = std::find(c.cbegin(), c.cend(), value);
    if (it != c.cend())
      return &*it;
    return nullptr;
  }

  /// 配列から値を探索する。
  /// @param[in]  a     配列
  /// @param[in]  value 探索する値
  /// @return     aの要素にvalueに一致する要素があればその要素へのポインタを返す。なければnullptrを返す。
  /// find関数との違いは、cfind関数はconst修飾されたポインタを返すことである。
  template <typename T, std::size_t N>
  inline auto cfind(T const (&a)[N], T value)
    -> T const*
  {
    auto p = std::find(a + 0, a + N, value);
    if (p != a + N)
      return p;
    return nullptr;
  }

  /// 連想コンテナから値を探索する。
  /// @param[in]  c     連想コンテナ
  /// @param[in]  key   探索するキー
  /// @return     cの要素にkeyに一致する要素があればその値へのポインタを返す。なければnullptrを返す。
  /// find関数との違いは、cfind関数はconstポインタを返すことである。
  template <typename C>
  inline auto cfind(C& c, typename C::key_type key)
    -> decltype(&c.cbegin()->second)
  {
    auto it = const_cast<std::add_const_t<C>&>(c).find(key);
    if (it != c.cend())
      return &it->second;
    return nullptr;
  }
}

#endif  // !MENON_BITS_FIND_HH_
