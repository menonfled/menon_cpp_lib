/// @file   menon/bits/strstr.hh
/// strstr系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRSTR_HH_
#define MENON_BITS_STRSTR_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <iterator>
#include <type_traits>

namespace menon
{
  template <typename Char, typename String>
  constexpr auto strstr(Char* s1, String const& s2)
    -> Char*
  {
    if (s1 == nullptr)
      return nullptr;

    using ::menon::sv;
    auto t = sv(s1);
    auto u = sv(s2);
    using sv_type = decltype(t);
    auto pos = t.find(u.data(), 0, u.size());
    if (pos == sv_type::npos)
      return nullptr;
    return s1 + pos;
  }

  template <typename String1, typename String2>
  constexpr auto strstr(String1 const& s1, String2 const& s2)
    -> decltype(std::begin(s1))
  {
    using ::menon::sv;
    auto t = sv(s1);
    auto u = sv(s2);
    using sv_type = decltype(t);
    static_assert(std::is_same_v<typename sv_type::value_type, typename decltype(u)::value_type>);
    auto pos = t.find(u.data(), 0, u.size());
    if (pos == sv_type::npos)
      return {};
    return std::begin(s1) + pos;
  }
}

#endif  // !MENON_BITS_STRSTR_HH_
