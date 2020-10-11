﻿/// @file   menon/bits/trim.hh
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
      if (pos == std::basic_string_view<Char, Traits>::npos)
        pos = 0;
      return { sv.cbegin() + pos, sv.cend() };
    }

    template <typename Char, typename Traits>
    constexpr auto rtrim_helper(std::basic_string_view<Char, Traits> sv, std::basic_string_view<Char, Traits> character_mask)
      -> std::basic_string_view<Char, Traits>
    {
      auto pos = sv.find_last_not_of(character_mask);
      if (pos == std::basic_string_view<Char, Traits>::npos)
        pos = sv.size() - 1;
      return { sv.cbegin(), sv.cbegin() + pos + 1 };
    }

    template <typename Char, typename Traits>
    constexpr auto trim_helper(std::basic_string_view<Char, Traits> sv, std::basic_string_view<Char, Traits> character_mask)
      -> std::basic_string_view<Char, Traits>
    {
      auto pos1 = sv.find_first_not_of(character_mask);
      if (pos1 == std::basic_string_view<Char, Traits>::npos)
        pos1 = 0;
      auto pos2 = sv.find_last_not_of(character_mask);
      if (pos2 == std::basic_string_view<Char, Traits>::npos)
        pos2 = sv.size() - 1;
      return { sv.cbegin() + pos1, sv.cbegin() + pos2 + 1 };
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

  /// 文字列の末尾から空白（または他の文字）を除去する。
  /// @param[in]  s               元の文字列
  /// @param[in]  character_mask  除去する文字の並び
  /// @return     sの末尾からcharacter_maskに含まれる文字を除いた部分文字列をsring_viewで返す。
  template <typename String1, typename String2>
  constexpr auto rtrim(String1 const& s, String2 const& character_mask )
  {
    using ::menon::sv;
    return detail::rtrim_helper(sv(s), sv(character_mask));
  }

  /// 文字列の末尾から空白を除去する。
  /// @param[in]  s               元の文字列
  /// @return     sの末尾から空白類文字を除いた部分文字列をsring_viewで返す。
  template <typename String>
  constexpr auto rtrim(String const& s)
  {
    using ::menon::sv;
    auto t = sv(s);
    using char_type = typename decltype(t)::value_type;
    return detail::rtrim_helper(t, sv(detail::default_character_mask<char_type>));
  }

  /// 文字列の両端から空白（または他の文字）を除去する。
  /// @param[in]  s               元の文字列
  /// @param[in]  character_mask  除去する文字の並び
  /// @return     sの両端からcharacter_maskに含まれる文字を除いた部分文字列をsring_viewで返す。
  template <typename String1, typename String2>
  constexpr auto trim(String1 const& s, String2 const& character_mask )
  {
    using ::menon::sv;
    return detail::trim_helper(sv(s), sv(character_mask));
  }

  /// 文字列の両端から空白を除去する。
  /// @param[in]  s               元の文字列
  /// @return     sの両端から空白類文字を除いた部分文字列をsring_viewで返す。
  template <typename String>
  constexpr auto trim(String const& s)
  {
    using ::menon::sv;
    auto t = sv(s);
    using char_type = typename decltype(t)::value_type;
    return detail::trim_helper(t, sv(detail::default_character_mask<char_type>));
  }
}

#endif  // !MENON_BITS_TRIM_HH_
