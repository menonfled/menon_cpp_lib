/// @file   menon/bits/strcat.hh
/// strcat系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRCAT_HH_
#define MENON_BITS_STRCAT_HH_
#pragma once

#include "menon/bits/strlen.hh"
#include "menon/bits/strcpy.hh"
#include <type_traits>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    auto strcat_helper(Char* s, std::size_t n, std::basic_string_view<Char, Traits> sv)
    {
      if (n == 0)
        return s;
      Expects(s != nullptr);

      auto length = strlen(s, n);
      strcpy(s + length, n - length, sv);
      return s;
    }
  }

  /// 文字列の連結
  /// @param[in,out]  s1    先行部分の文字列および結果の格納先
  /// @param[in]      n     s1が指す配列の要素数
  /// @param[in]      s2    連結するの文字列
  /// @return         s1を返す。
  /// s1に格納されている文字列にs2が指す文字列を連結し、結果をs1に格納する。
  /// nが1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, typename String>
  auto strcat(Char* s1, std::size_t n, String const& s2)
  {
    using ::menon::sv;
    return detail::strcat_helper(s1, n, sv(s2));
  }

  /// 文字列の連結
  /// @param[in,out]  s1    先行部分の文字列および結果の格納先
  /// @param[in]      s2    連結するの文字列
  /// @return         s1を返す。
  /// s1に格納されている文字列にs2が指す文字列を連結し、結果をs1に格納する。
  /// nが1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, std::size_t N, typename String>
  auto strcat(Char (&s1)[N], String const& s2)
  {
    using ::menon::sv;
    return detail::strcat_helper(s1, N, sv(s2));
  }

  /// 文字列の連結
  /// @param[in,out]  s1    先行部分の文字列および結果の格納先
  /// @param[in]      s2    連結するの文字列
  /// @return         s1を返す。
  /// s1に格納されている文字列にs2が指す文字列を連結し、結果をs1に格納する。
  template <typename Char, typename Traits, typename Allocator, typename String>
  auto strcat(std::basic_string<Char, Traits, Allocator>& s1, String const& s2)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    using ::menon::sv;
    auto ss2 = sv(s2);
    static_assert(std::is_same_v<Char, typename decltype(ss2)::value_type>);
    return s1.append(ss2.cbegin(), ss2.cend());
  }

  /// 指定文字数だけ文字列を連結
  /// @param[in,out]  s1    先行部分の文字列および結果の格納先
  /// @param[in]      n1    s1が指す配列の要素数
  /// @param[in]      s2    連結するの文字列
  /// @param[in]      n2    指定文字数
  /// @return         s1を返す。
  /// s1に格納されている文字列にs2が指す文字列を連結し、結果をs1に格納する。
  /// nが1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, typename String>
  auto strncat(Char* s1, std::size_t n1, String const& s2, std::size_t n2)
  {
    using ::menon::sv;
    return detail::strcat_helper(s1, n1, sv(s2).substr(0, n2));
  }

  /// 指定文字数だけ文字列を連結
  /// @param[in,out]  s1    先行部分の文字列および結果の格納先
  /// @param[in]      s2    連結するの文字列
  /// @param[in]      n     指定文字数
  /// @return         s1を返す。
  /// s1に格納されている文字列にs2が指す文字列を連結し、結果をs1に格納する。
  /// nが1要素以上ある場合、s1には必ずナル文字を格納する。
  /// @attention  文字列が切り詰められることで予期しない結果になる場合があるので要注意。  
  template <typename Char, std::size_t N, typename String>
  auto strncat(Char (&s1)[N], String const& s2, std::size_t n)
  {
    using ::menon::sv;
    return detail::strcat_helper(s1, N, sv(s2).substr(0, n));
  }

  /// 指定文字数だけ文字列を連結
  /// @param[in,out]  s1    先行部分の文字列および結果の格納先
  /// @param[in]      s2    連結するの文字列
  /// @param[in]      n     指定文字数
  /// @return         s1を返す。
  /// s1に格納されている文字列にs2が指す文字列を連結し、結果をs1に格納する。
  template <typename Char, typename Traits, typename Allocator, typename String>
  auto strncat(std::basic_string<Char, Traits, Allocator>& s1, String const& s2, std::size_t n)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    using ::menon::sv;
    auto ss2 = sv(s2).substr(0, n);
    static_assert(std::is_same_v<Char, typename decltype(ss2)::value_type>);
    return s1.append(ss2.cbegin(), ss2.cend());
  }
}

#endif  // !MENON_BITS_STRCAT_HH_
