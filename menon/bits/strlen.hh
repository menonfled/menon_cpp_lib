/// @file   menon/bits/strlen.hh
/// @author @menonfled
/// strlen関数の定義
#ifndef MENON_BITS_STRLEN_HH_
#define MENON_BITS_STRLEN_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <cstddef>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    constexpr auto strlen_helper(std::basic_string_view<Char, Traits> sv)
    {
      return sv.size();
    }
  }

  /// 文字列の長さを求める
  /// @param[in]  s   文字列
  /// @return     文字列sの（ナル文字を除く）要素数を返す。
  /// 標準関数のstrlenの利便性を向上した関数。
  /// 文字型へのポインタのほか、basic_stringやbasic_string_viewを渡すことも可能。
  template <typename T>
  constexpr auto strlen(T s)
  {
    using menon::sv;
    return detail::strlen_helper(sv(s));
  }

  /// 文字列の長さを求める
  /// @param[in]  s   文字列
  /// @param[in]  n   sが指す配列の要素数
  /// @return     文字列sの（ナル文字を除く）要素数を返す。
  /// 標準関数のstrlenの利便性を向上した関数。
  template <typename Char>
  constexpr auto strlen(Char const* s, std::size_t n)
  {
    using menon::sv;
    return detail::strlen_helper(sv(s, n));
  }
}

#endif  // !MENON_BITS_STRLEN_HH_
