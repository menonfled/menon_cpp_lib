/// @file   menon/bits/strcmp.hh
/// strcmp系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_STRCMP_HH_
#define MENON_BITS_STRCMP_HH_
#pragma once

#include "menon/bits/sv.hh"
#include "menon/bits/toctrans.hh"

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    inline auto strcmp_helper(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2)
    {
      return sv1.compare(sv2);
    }

    template <typename Char, typename Traits>
    inline auto strncmp_helper(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2, std::size_t n)
    {
      return sv1.compare(0, n, sv2, 0, n);
    }

    template <typename Char, typename Traits>
    auto strcasecmp_helper(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2)
      -> int
    {
      auto ss1 = sv1.cbegin();
      auto ss2 = sv2.cbegin();

      while (ss1 != sv1.cend() && sv2.cend())
      {
        if (auto r = static_cast<int>(tolower(*ss1) - tolower(*ss2)))
          return r;
        ++ss1;
        ++ss2;
      }
      return 0;
    }

    template <typename Char, typename Traits>
    inline auto strncasecmp_helper(std::basic_string_view<Char, Traits> sv1, std::basic_string_view<Char, Traits> sv2, std::size_t n)
    {
      return strcasecmp_helper(sv1.substr(0, n), sv2.substr(0, n));
    }
  }

  /// 文字列の比較
  /// @param[in]  s1  比較対象の文字列
  /// @param[in]  s2  比較対象の文字列
  /// @retuen     s1 < s2のときは負、s1 == s2のときは0、s1 > s2のときは正の値を返す。
  template <typename T, typename U>
  inline auto strcmp(T const& s1, U const& s2)
  {
    using menon::sv;
    return detail::strcmp_helper(sv(s1), sv(s2));
  }

  /// 指定文字数だけ文字列を比較
  /// @param[in]  s1  比較対象の文字列
  /// @param[in]  s2  比較対象の文字列
  /// @param[in]  n   指定文字数
  /// @retuen     s1 < s2のときは負、s1 == s2のときは0、s1 > s2のときは正の値を返す。
  template <typename T, typename U>
  inline auto strncmp(T const& s1, U const& s2, std::size_t n)
  {
    using menon::sv;
    return detail::strncmp_helper(sv(s1), sv(s2), n);
  }

  /// 大文字小文字を区別しない文字列の比較
  /// @param[in]  s1  比較対象の文字列
  /// @param[in]  s2  比較対象の文字列
  /// @retuen     s1 < s2のときは負、s1 == s2のときは0、s1 > s2のときは正の値を返す。
  template <typename T, typename U>
  inline auto strcasecmp(T const& s1, U const& s2)
  {
    using menon::sv;
    return detail::strcasecmp_helper(sv(s1), sv(s2));
  }

  /// 指定文字数だけ大文字小文字を区別せずに文字列を比較
  /// @param[in]  s1  比較対象の文字列
  /// @param[in]  s2  比較対象の文字列
  /// @param[in]  n   指定文字数
  /// @retuen     s1 < s2のときは負、s1 == s2のときは0、s1 > s2のときは正の値を返す。
  template <typename T, typename U>
  inline auto strncasecmp(T const& s1, U const& s2, std::size_t n)
  {
    using menon::sv;
    return detail::strncasecmp_helper(sv(s1), sv(s2), n);
  }
}

#endif  // !MENON_BITS_STRCMP_HH_
