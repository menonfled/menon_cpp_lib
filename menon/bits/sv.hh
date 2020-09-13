/// @file menon/bits/sv.hh
/// @aothor @menonfled
/// さまざまな形式の文字列をstring_viewに変換するためのヘルパー関数の定義
#ifndef MENON_BITS_SV_HH_
#define MENON_BITS_SV_HH_
#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <type_traits>
#include <array>
#include "menon/bits/config.hh"
#if MENON_HAS_BOOST
#include <boost/utility/string_view.hpp>
#endif

namespace menon
{
  /// 1文字からstring_viewへの変換
  /// @param[in]  c   変換対象の文字
  /// @return     cの型に応じたstd::basic_string_view
  template <typename Char>
  constexpr auto sv(Char const& c)
  {
    return std::basic_string_view<Char>(&c, 1);
  }

  /// ナル終端からstring_viewへの変換
  /// @param[in]  s   変換対象の文字列
  /// @return     sの型に応じたstd::basic_string_view
  template <typename Char>
  constexpr auto sv(Char* s)
    -> std::basic_string_view<std::remove_const_t<Char>>
  {
    if (s == nullptr)
      return {};
    return s;
  }

  /// 文字配列からstring_viewへの変換
  /// @param[in]  s   変換対象の文字列
  /// @param[in]  n   文字列の長さ 
  /// @return     sの型に応じたstd::basic_string_view
  template <typename Char>
  constexpr auto sv(Char* s, std::size_t n)
    -> std::basic_string_view<std::remove_const_t<Char>>
  {
    if (s == nullptr)
      return {};
    return { s, n };
  }

  /// string_viewからstring_viewへの変換
  /// @param[in]  sv  変換対象の文字列
  /// @return     sv
  template <typename Char, typename Traits>
  constexpr auto sv(std::basic_string_view<Char, Traits> sv)
  {
    return sv;
  }

  /// stringからstring_viewへの変換
  /// @param[in]  str 変換対象の文字列
  /// @return     strの型に応じたstd::basic_string_view
  template <typename Char, typename Traits, typename Allocator>
  constexpr auto sv(std::basic_string<Char, Traits, Allocator> str)
  {
    return std::basic_string_view<Char, Traits>(str);
  }

#if MENON_HAS_GSL
  /// gsl::string_spanからstring_viewへの変換
  /// @param[in]  ss  変換対象の文字列
  /// @return     ssの型に応じたstd::basic_string_view
  template <typename Char, std::size_t Extent>
  constexpr auto sv(gsl::basic_string_span<Char, Extent> ss)
  {
    return std::basic_string_view<Char>(ss.data(), ss.size());
  }
#endif

#if MENON_HAS_BOOST
  /// boost::string_viewからstring_viewへの変換
  /// @param[in]  sv  変換対象の文字列
  /// @return     svの型に応じたstd::basic_string_view
  template <typename Char, typename Traits>
  constexpr auto sv(boost::basic_string_view<Char, Traits> sv)
  {
    return std::basic_string_view<Char, Traits>(sv.data(), sv.size());
  }
#endif

  /// arrayからstring_viewへの変換
  /// @param[in]  sv    string_view文字列
  /// @return     svの内容を変換したarrayを返す。
  /// この関数を呼び出す際は明示的にarraryの要素数Nを指定する必要がある。
  /// Nがsv.size()より小さい場合はNだけコピーされる。
  /// 逆にNがsv.size()より大きい場合は余った要素にナル文字を格納する。
  template <std::size_t N, typename Char, typename Traits>
  constexpr auto sv_to_array(std::basic_string_view<Char, Traits> sv)
  {
    std::array<Char, N> r {};
    std::size_t n = sv.size();
    if (N < n)
      n = N;
    for (std::size_t i = 0; i < n; i++)
      r[i] = sv[i];
    return r;
  }
}

#endif  // !MENON_BITS_SV_HH_
