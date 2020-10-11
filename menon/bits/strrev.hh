/// @file   menon/bits/strrev.hh
/// strrev関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRREV_HH_
#define MENON_BITS_STRREV_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <algorithm>
#include <string>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    inline auto strrev_helper(std::basic_string_view<Char, Traits> sv)
      -> std::basic_string<Char, Traits>
    {
      return { sv.crbegin(), sv.crend() };
    }
  }

  /// 文字の並びを逆順にした文字列を返す。
  /// @param[in]  s     元の文字列
  /// @return     sを逆順にした文字列をbasic_stringとして返す。
  /// UTF-8などの多バイト文字、UTF-16のサロゲートペアなどは考慮しないので要注意
  template <typename String>
  inline auto strrev(String const& s)
  {
    using ::menon::sv;
    return detail::strrev_helper(sv(s));
  }
}

#endif  // !MENON_BITS_STRREV_HH_
