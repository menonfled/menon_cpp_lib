/// @file   menon/bits/strto.hh
/// strto*系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRTO_HH_
#define MENON_BITS_STRTO_HH_
#pragma once

#include "menon/bits/sv.hh"
#include "menon/bits/alnum.hh"
#include "menon/bits/isctype.hh"
#include "menon/bits/toctrans.hh"
#include <cstring>
#include <concepts>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <type_traits>

namespace menon
{
  namespace detail
  {
    // 先行する空白類文字と符号の処理
    template <std::input_iterator InputIterator>
    auto space_sign(InputIterator& next, InputIterator last)
    {
      bool negative = 0;
      while (next != last)
      {
        auto c = *next;
        if (!std::isspace(c))
          break;
        ++next;
      }
      switch (*next)
      {
        case '-':
          negative = true;
          [[fallthrough]];
        case '+':
          ++next;
          break;
        default:
          break;
      }
      return negative;
    }

    // radixに0を指定した場合の基数判定
    template <std::input_iterator InputIterator>
    auto default_radix(InputIterator& next, InputIterator last)
    {
      int radix = 10;
      auto c = *next;
      using char_type = decltype(c);
      if (c == static_cast<char_type>('0'))
      {
        radix = 8;
        if (++next != last)
        {
          c = tolower(*next);
          if (c == static_cast<char_type>('x'))
          {
            radix = 16;
            ++next;
          }
        }
      }
      return radix;
    }

    // 整数部の解析
    template <typename T, std::input_iterator InputIterator>
    auto strto_helper(InputIterator& next, InputIterator last, int radix, bool* overflow)
    {
      T r = 0;
      while (next != last)
      {
        r *= radix;
        auto c = tolower(*next);
        if (c > 0x7e)
          break;
        if (auto ptr = std::strchr(detail::alnum, c))
        {
          auto d = static_cast<T>(ptr - detail::alnum);
          if (r + d <= r)
            *overflow = true;
          r += d;
          ++next;
        }
        else
        {
          break;
        }
      }
      return r;
    }
  }

  /// 文字列から整数への変換
  /// @param[in]  s       変換対象の文字列
  /// @param[out] endpos  解析を終えた位置
  /// @param[in]  radix   基数（0, 2～36）
  template <std::integral T, typename String>
  auto strto(String const& s, std::size_t* endpos = nullptr, int radix = 0)
    -> T
  {
    using ::menon::sv;
    using unsigned_type = std::make_unsigned_t<T>;

    Expects(radix == 0 || (2 <= radix && radix <= 36));
    auto t = sv(s);
    auto next = t.cbegin();
    auto last = t.cend();
    int sign = detail::space_sign(next, last);
    if (radix == 0)
      radix = detail::default_radix(next, last);

    // 符号無し整数として解析する。
    bool overflow;
    auto r = detail::strto_helper<unsigned_type>(next, last, radix, &overflow);

    if (overflow)
      throw std::overflow_error("menon::strto");
    // 符号付き整数の場合はオーバーフロー判定を追加
    if constexpr (std::is_signed_v<T>)
    {
      if ((!sign && r > std::numeric_limits<T>::max())
        || (sign && r > -static_cast<unsigned_type>(std::numeric_limits<T>::min())))
        throw std::overflow_error("menon::strto");
    }
    if (endpos)
      *endpos = static_cast<std::size_t>(next - t.cbegin());
    return static_cast<T>(sign ? -r : r);
  }
}

#endif  // !MENON_BITS_STRTO_HH_
