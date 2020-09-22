/// @file   menon/bits/strchr.hh
/// strchr系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRCHR_HH_
#define MENON_BITS_STRCHR_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <iterator>
#include <type_traits>

namespace menon
{
  /// 文字列中の文字列を探索
  /// @param[in]  s     探索対象の文字列
  /// @param[in]  c     探索する文字
  /// @return     文字が見つかればその文字へのポインタを、見つからなければnullptrを返す。
  /// 標準関数のstrchrと同じだが、constexprにできる点が異なる。
  template <typename Char>
  constexpr auto strchr(Char* s, std::remove_cv_t<Char> c)
    -> Char*
  {
    if (s == nullptr)
      return nullptr;

    using ::menon::sv;
    auto t = sv(s);
    using sv_type = decltype(t);
    auto pos = t.find(static_cast<typename sv_type::value_type>(c));
    if (pos == sv_type::npos)
      return nullptr;
    return s + pos;
  }

  /// 文字列中の文字列を探索
  /// @param[in]  s     探索対象の文字列
  /// @param[in]  c     探索する文字
  /// @return     文字が見つかればその文字への反復子を、見つからなければ空の反復子を返す。
  /// 標準関数のstrchrと同じだが、stringやstring_viewに対しても使用できる。
  template <typename String, typename Char>
  constexpr auto strchr(String const& s, Char c)
    -> decltype(std::begin(s))
  {
    using ::menon::sv;
    auto t = sv(s);
    using sv_type = decltype(t);
    auto pos = t.find(static_cast<typename sv_type::value_type>(c));
    if (pos == sv_type::npos)
      return {};
    return std::begin(s) + pos;
  }
}

#endif  // !MENON_BITS_STRCHR_HH_
