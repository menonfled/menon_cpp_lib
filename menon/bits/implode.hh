/// @file   menon/bits/implode.hh
/// implode関数の定義
/// @author @menonfled
#ifndef MENON_BITS_IMPLODE_HH_
#define MENON_BITS_IMPLODE_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <iterator>
#include <initializer_list>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits, typename InputIterator>
    auto implode_helper(std::basic_string_view<Char, Traits> glue, InputIterator first, InputIterator last)
      -> std::basic_string<Char, Traits>
    {
      using ::menon::sv;
      std::basic_string<Char, Traits> r;

      while (first != last)
      {
        r += sv(*first);
        if (++first != last)
          r += glue;
      }
      return r;
    }
  }

  /// 文字列の列要素を連結する。
  /// @param[in]  glue  区切り文字
  /// @param[in]  c     文字列の列
  /// @return     連結した結果をstringとして返す。
  /// この関数はPHPのimplodeからの借用である。
  template <typename T, typename U>
  auto implode(T const& glue, U const& c)
  {
    using ::std::begin;
    using ::std::end;
    using ::menon::sv;
    return detail::implode_helper(sv(glue), begin(c), end(c));
  }

  /// 文字列の列要素を連結する。
  /// @param[in]  glue  区切り文字
  /// @param[in]  il    文字列の列
  /// @return     連結した結果をstringとして返す。
  template <typename T, typename U>
  auto implode(T const& glue, std::initializer_list<U> il)
  {
    using ::menon::sv;
    return detail::implode_helper(sv(glue), il.begin(), il.end());
  }

  /// 文字列の列要素を連結する。
  /// @param[in]  glue  区切り文字
  /// @param[in]  first 文字列の列の先頭を指す反復子
  /// @param[in]  last  文字列の列の末尾の次を指す反復子
  /// @return     連結した結果をstringとして返す。
  template <typename T, typename InputIterator>
  auto implode(T const& glue, InputIterator first, InputIterator last)
  {
    using ::menon::sv;
    return detail::implode_helper(sv(glue), first, last);
  }
}

#endif  // !MENON_BITS_IMPLODE_HH_
