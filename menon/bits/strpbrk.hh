/// @file   menon/bits/strpbrk.hh
/// strpbrk系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRPBRK_HH_
#define MENON_BITS_STRPBRK_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <iterator>
#include <type_traits>

namespace menon
{
  /// 文字列中の文字群探索
  /// @param[in]  s1    探索対象の文字列
  /// @param[in]  s2    探索する文字群
  /// @return     s1中でs2に含まれる文字のいずれかが最初に現れた位置からの部分文字列を返す。
  /// 標準関数のstrpbrk関数と同様だが以下の点が異なる。
  ///
  /// - constexprにできる。
  /// - stringやbasic_stringを指定できる。
  /// - 返却値はポインタではなくstring_viewである。
  template <typename String1, typename String2>
  constexpr auto strpbrk(String1 const& s1, String2 const& s2)
  {
    using ::menon::sv;
    auto t = sv(s1);
    auto u = sv(s2);
    static_assert(std::is_same_v<typename decltype(t)::value_type, typename decltype(u)::value_type>);
    auto pos = t.find_first_of(u);
    return t.substr(pos);
  }
}

#endif  // !MENON_BITS_STRPBRK_HH_
