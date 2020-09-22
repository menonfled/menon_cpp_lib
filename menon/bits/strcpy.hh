/// @file   menon/bits/strcpy.hh
/// strcpy系関数の定義
/// @author @menofled
#ifndef MENON_BITS_STRCPY_HH_
#define MENON_BITS_STRCPY_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <algorithm>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    auto strcpy_helper(Char* s, std::size_t n, std::basic_string_view<Char, Traits> sv)
    {
      if (n == 0)
        return s;
      Expects(s != nullptr);

      if (n > sv.size() + 1)
        n = sv.size() + 1;
      std::copy_n(sv.cbegin(), n - 1, s);
      s[n - 1] = {};
      return s;
    }
  }

  /// 文字列のコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  n     s1が指す配列の要素数
  /// @param[in]  s2    コピー元の文字列
  /// @return     s1を返す。
  /// nが1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, typename String>
  inline auto strcpy(Char* s1, std::size_t n, String const& s2)
  {
    using ::menon::sv;
    return detail::strcpy_helper(s1, n, sv(s2));
  }

  /// 文字列のコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  s2    コピー元の文字列
  /// @return     s1を返す。
  /// s1が1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, std::size_t N, typename String>
  inline auto strcpy(Char (&s1)[N], String const& s2)
  {
    using ::menon::sv;
    return detail::strcpy_helper(s1, N, sv(s2));
  }

  /// 文字列のコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  s2    コピー元の文字列
  /// @return     s1を返す。
  template <typename Char, typename Traits, typename Allocator, typename String>
  inline auto strcpy(std::basic_string<Char, Traits, Allocator>& s1, String const& s2)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    using ::menon::sv;
    auto t = sv(s2);
    s1.assign(t.cbegin(), t.cend());
    return s1;
  }

  /// 指定文字数だけ文字列をコピー
  /// @param[out] s1    コピー結果の格納先
  /// @param[in]  s2    コピー元の文字列
  /// @param[in]  n     コピーする要素数
  /// @return     s1を返す。
  /// 標準関数のstrncpy関数同様、必ずn要素だけs1に書き込む。
  /// s2の長さがnに満たない場合、残りの領域にはナル文字を書き込む。
  /// s2の長さがn以上の場合はナル文字が書き込まれない。
  template <typename Char, typename String>
  auto strncpy(Char* s1, String const& s2, std::size_t n)
  {
    if (n == 0)
      return s1;
    Expects(s1 != nullptr);

    using ::menon::sv;
    auto t = sv(s2);
    auto length = std::min(static_cast<std::size_t>(t.size()), n);
    t.copy(s1, length);
    if (length < n)
      std::fill_n(s1 + length, n - length, Char('\0'));
    return s1;
  }
}

#endif  // !MENON_BITS_STRCPY_HH_
