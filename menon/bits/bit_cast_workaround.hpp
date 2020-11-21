/// @file   menon/bits/bit_cast_workaround.hh
/// bit_castの代替定義
/// @authoe @menonfled
#ifndef MENON_BITS_BIT_CAST_WORKAROUND_HH_
#define MENON_BITS_BIT_CAST_WORKAROUND_HH_
#pragma once

#include <bit>

namespace menon
{
  template<typename To, typename From>
  constexpr To bit_cast(From const& from) noexcept
  {
#ifdef _MSC_VER
    return std::bit_cast<To>(from);
#elif __clang__
    return __builtin_bit_cast(To, from);
#else
    return reinterpret_cast<To const&>(from);
#endif
  }
}

#endif  // MENON_BITS_BIT_CAST_WORKAROUND_HH_