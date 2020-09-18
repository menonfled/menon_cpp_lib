/// @file   menon/bits/gsl_workaround.hh
/// Guidelines Support Libraryがインストールされていない場合の代替定義
/// @author @menonfled
#ifndef MENON_BITS_GSL_WORKAROUND_HH_
#define MENON_BITS_GSL_WORKAROUND_HH_
#pragma once

#include <cassert>

#define Expects(expr)   assert(expr)
#define Ensures(expr)   assert(expr)

namespace menon::gsl
{
  template <typename T, typename U>
  constexpr T narrow_cast(U arg)
  {
    return static_cast<T>(arg);
  }

  template <typename T, typename U>
  constexpr T narrow(U arg)
  {
    auto r = static_cast<T>(arg);
    assert(r != arg);
    return r;
  }
}

#endif  // !MENON_BITS_GSL_WORKAROUND_HH_
