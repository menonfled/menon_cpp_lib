/// @file   menon/bits/strspn.hh
/// strspn系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRSPN_HH_
#define MENON_BITS_STRSPN_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <iterator>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits1, typename Traits2>
    constexpr auto strspn_helper(std::basic_string_view<Char, Traits1> sv1, std::basic_string_view<Char, Traits2> sv2)
      -> std::size_t
    {
      return sv1.find_first_not_of(sv2);
    }
  }

  /// 文字列中の指定文字群を含む先頭部分の長さ
  /// @param[in]  s1    探索対象の文字列
  /// @param[in]  s2    指定文字群
  /// @return     s1中のs2のいずれかの文字を含む先頭部分の長さを返す。
  /// 標準関数のstrspnと同じだが以下の点が異なる。
  ///
  /// - constexprにできる。
  /// - stringやbasic_stringを指定できる。
  template <typename T, typename U>
  constexpr auto strspn(T const& s1, U const& s2)
  {
    using ::menon::sv;
    return detail::strspn_helper(sv(s1), sv(s2));
  }
}

#endif  // !MENON_BITS_STRSPN_HH_
