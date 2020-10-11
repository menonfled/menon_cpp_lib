/// @file   menon/bits/trim.hh
/// trim系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_TRIM_HH_
#define MENON_BITS_TRIM_HH_
#pragma once

#include "menon/bits/sv.hh"

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    constexpr auto ltrim_helper(std::basic_string_view<Char, Traits> sv, std::basic_string_view<Char, Traits> character_mask)
      -> std::basic_string_view<Char, Traits>
    {
      auto pos = sv.find_first_not_of(character_mask);
      return { sv.cbegin() + pos, sv.cend() };
    }

    template <typename Char>
    constexpr Char const default_character_mask[] =
    {
      Char(' '),
      Char('\t'),
      Char('\r'),
      Char('\n'),
      Char('\v'),
      Char('\0')
    };
  }

  /// 文字列の先頭から空白（または他の文字）を除去する。
  /// @param[in]  s               元の文字列
  /// @param[in]  character_mask  除去する文字の並び
  /// @return     sの先頭からcharacter_maskに含まれる文字を除いた部分文字列をsring_viewで返す。
  template <typename String1, typename String2>
  constexpr auto ltrim(String1 const& s, String2 const& character_mask )
  {
    using ::menon::sv;
    return detail::ltrim_helper(sv(s), sv(character_mask));
  }

  /// 文字列の先頭から空白を除去する。
  /// @param[in]  s               元の文字列
  /// @return     sの先頭から空白類文字を除いた部分文字列をsring_viewで返す。
  template <typename String>
  constexpr auto ltrim(String const& s)
  {
    using ::menon::sv;
    auto t = sv(s);
    using char_type = typename decltype(t)::value_type;
    return detail::ltrim_helper(t, sv(detail::default_character_mask<char_type>));
  }
}

#endif  // !MENON_BITS_TRIM_HH_
