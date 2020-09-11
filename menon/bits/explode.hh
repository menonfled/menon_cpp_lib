/// @file   menon/bits/explode.hh
/// @author @menonfled
/// explode関数の定義
#ifndef MENON_BITS_EXPLODE_HH_
#define MENON_BITS_EXPLODE_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <vector>
#include <iterator>
#include <climits>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits, typename Target>
    auto explode_helper(std::basic_string_view<Char, Traits> delimiter, std::basic_string_view<Char, Traits> str, Target& r, int limit)
    {
      using sv_type = std::basic_string_view<Char, Traits>;
      using size_type = typename sv_type::size_type;
      using value_type = typename Target::value_type;
      size_type pos = 0;
      size_type pos2 = 0;
      size_type npos = sv_type::npos;
      size_type delimiter_size = delimiter.size();

      if (limit == 0)
        limit = 1;

      if (!str.empty())
      {
        int n = 1;
        while (pos2 != npos)
        {
          pos2 = str.find(delimiter, pos);
          r.push_back(value_type(str.substr(pos, pos2 - pos)));
          pos = pos2 + delimiter_size;

          if (limit > 0 && ++n >= limit)
          {
            r.push_back(value_type(str.substr(pos)));
            break;
          }
        }
        if (limit < 0)
        {
          auto it = r.begin();
          std::advance(it, r.size() + limit);
          r.erase(it, r.end());
        }
      }
    }
  }

  /// 文字列を文字（列）により分割する
  /// @param[in]  delimiter 区切り文字（列）
  /// @param[in]  str       分割対象の文字列
  /// @param[in]  limit     結果の最大要素
  /// @return     分割した文字列をstring_viewのvectorとして返す。
  /// この関数はPHPのexplodeからの借用である。
  /// 
  /// - limitが正の場合、結果には最大limitの要素が含まれ、その最後の要素にはstrの残りの部分が含まれる。
  /// - limitが負の場合、最後の-limit個を除くすべての要素が返される。
  /// - limitが0の場合、1を指定したものとして扱われる。
  template <typename T, typename U>
  auto explode(T delimiter, U str, int limit = INT_MAX)
  {
    using ::menon::sv;
    auto s = sv(str);
    std::vector<decltype(s)> r;
    detail::explode_helper(sv(delimiter), s, r, limit);
    return r;
  }

  /// 文字列を文字（列）により分割する
  /// @param[in]  delimiter 区切り文字（列）
  /// @param[in]  str       分割対象の文字列
  /// @param[in]  r         分割結果の格納先
  /// @param[in]  limit     結果の最大要素
  /// @return     rを返す。
  /// 
  /// - limitが正の場合、結果には最大limitの要素が含まれ、その最後の要素にはstrの残りの部分が含まれる。
  /// - limitが負の場合、最後の-limit個を除くすべての要素が返される。
  /// - limitが0の場合、1を指定したものとして扱われる。
  ///
  /// 分割結果の格納先をrで指定することができる。
  /// これにより、string_viewのvectorだけでなく、stringのvectorやlistなどを用いることもできる。
  template <typename T, typename U, typename Target>
  auto explode(T delimiter, U str, Target& r, int limit = INT_MAX)
    -> Target&
  {
    using ::menon::sv;
    detail::explode_helper(sv(delimiter), sv(str), r, limit);
    return r;
  }
}

#endif  // !MENON_BITS_EXPLODE_HH_
