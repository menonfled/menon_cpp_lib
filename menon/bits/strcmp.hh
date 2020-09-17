/// @file   menon/bits/strcmp.hh
/// @author @menonfled
/// strcmp関数の定義
#ifndef MENON_BITS_STRCMP_HH_
#define MENON_BITS_STRCMP_HH_
#pragma once

#include "menon/bits/sv.hh"

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    constexpr auto strcmp(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2)
    {
      return sv1.compare(sv2);
    }
  }

  template <typename T, typename U>
  constexpr auto strcmp(T const& s1, U const& s2)
  {
    using menon::sv;
    return detail::strcmp(sv(s1), sv(s2));
  }
}

#endif  // !MENON_BITS_STRCMP_HH_
