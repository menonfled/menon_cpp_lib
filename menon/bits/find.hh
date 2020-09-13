#ifndef MENON_BITS_FIND_HH_
#define MENON_BITS_FIND_HH_
#pragma once

#include "menon/bits/config.hh"
#include <algorithm>

namespace menon
{
  template <typename C>
  inline auto find(C& c, typename C::value_type value)
    -> decltype(&*c.begin())
  {
    auto it = std::find(c.begin(), c.end(), value);
    if (it != c.end())
      return &*it;
    return nullptr;
  }
}

#endif  // !MENON_BITS_FIND_HH_
