/// @file   menon/bits/substr.hh
/// substr系関数の定義
/// @author menonfled
#ifndef MENON_BITS_SUBSTR_HH_
#define MENON_BITS_SUBSTR_HH_

#include "menon/bits/sv.hh"
#include <cstdint>

namespace menon
{
  template <typename String>
  constexpr auto substr(String const& s, std::size_t pos, std::size_t n = SIZE_MAX)
  {
    using ::menon::sv;
    return sv(s).substr(pos, n);
  }
}

#endif  // !MENON_BITS_SUBSTR_HH_