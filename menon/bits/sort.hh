/// @file   menon/bits/sort.hh
/// sort系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_SORT_HH_
#define MENON_BITS_SORT_HH_
#pragma once

#include "menon/bits/config.hh"
#include <algorithm>
#include <iterator>
#include <functional>
#include <list>

namespace menon
{
  /// コンテナを整列する。
  /// @param[in]  container   コンテナ
  /// @return     無し
  template <typename C>
  constexpr auto sort(C& container)
  {
    std::sort(std::begin(container), std::end(container));
  }

  /// リストを整列する。
  /// @param[in]  list      リスト
  /// @return     無し
  template <typename T, typename Allocator>
  inline auto sort(std::list<T, Allocator>& list)
  {
    list.sort();
  }

  /// コンテナを整列する。
  /// @param[in]  container   コンテナ
  /// @param[in]  comp      比較関数
  /// @return     無し
  template <typename C, typename Compare>
  constexpr auto sort(C& container, Compare comp)
  {
    std::sort(std::begin(container), std::end(container), comp);
  }

  /// リストを整列する。
  /// @param[in]  list      リスト
  /// @param[in]  comp      比較関数
  /// @return     無し
  template <typename T, typename Allocator, typename Compare>
  inline auto sort(std::list<T, Allocator>& list, Compare comp)
  {
    list.sort(comp);
  }

  /// コンテナを安定ソートで整列する。
  /// @param[in]  container   コンテナ
  /// @return     無し
  template <typename C>
  inline auto stable_sort(C& container)
  {
    std::stable_sort(std::begin(container), std::end(container));
  }

  /// リストを安定ソートで整列する。
  /// @param[in]  list      リスト
  /// @return     無し
  template <typename T, typename Allocator>
  inline auto stable_sort(std::list<T, Allocator>& list)
  {
    list.sort();
  }

  /// コンテナを安定ソートで整列する。
  /// @param[in]  container   コンテナ
  /// @param[in]  comp      比較関数
  /// @return     無し
  template <typename C, typename Compare>
  constexpr auto stable_sort(C& container, Compare comp)
  {
    std::stable_sort(std::begin(container), std::end(container), comp);
  }

  /// リストを安定ソートで整列する。
  /// @param[in]  list      リスト
  /// @param[in]  comp      比較関数
  /// @return     無し
  template <typename T, typename Allocator, typename Compare>
  inline auto stable_sort(std::list<T, Allocator>& list, Compare comp)
  {
    list.sort(comp);
  }
}

#endif  // !MENON_BITS_SORT_HH_
