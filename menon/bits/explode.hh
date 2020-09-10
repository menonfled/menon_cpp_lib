/// @file   menon/bits/explode.hh
/// @author @menonfled
/// explode関数の定義
#ifndef MENON_BITS_EXPLODE_HH_
#define MENON_BITS_EXPLODE_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <vector>
#include <climits>

namespace menon
{
  namespace detail
  {
    template <typename Char, typename Traits>
    auto explode_helper(std::basic_string_view<Char, Traits> delimiter, std::basic_string_view<Char, Traits> str, int limit)
      -> std::vector<std::basic_string_view<Char, Traits>>
    {
      using sv_type = std::basic_string_view<Char, Traits>;
      using size_type = typename sv_type::size_type;
      size_type pos = 0;
      size_type pos2 = 0;
      size_type npos = sv_type::npos;
      size_type delimiter_size = delimiter.size();

      std::vector<sv_type> r;
      if (limit == 0)
        limit = 1;

      if (!str.empty())
      {
        int n = 1;
        while (pos2 != npos)
        {
          pos2 = str.find(delimiter, pos);
          auto element = str.substr(pos, pos2 - pos);
          r.push_back(element);
          pos = pos2 + delimiter_size;

          if (limit > 0 && ++n >= limit)
          {
            r.push_back(str.substr(pos));
            break;
          }
        }
        if (limit < 0)
        {
          r.erase(r.begin() + r.size() + limit, r.end());
        }
      }
      return r;
    }
  }

  /// 文字列を文字（列）により分割する
  /// @param[in]  delimiter 区切り文字（列）
  /// @param[in]  str       分割対象の文字列
  /// @param[in]  limit     結果の最大要素
  /// @return     分割した文字列をstring_viewのvectorとして返す。
  /// この関数はPHPのexplodeからの借用である。
  /// 
  /// limitが正の場合、結果には最大limitの要素が含まれ、その最後の要素にはstrの残りの部分が含まれる。
  /// limitが負の場合、最後の-limit個を除くすべての要素が返される。
  /// limitが0の場合、1を指定したものとして扱われる。
  template <typename T, typename U>
  auto explode(T delimiter, U str, int limit = INT_MAX)
  {
    using ::menon::sv;
    return detail::explode_helper(sv(delimiter), sv(str), limit);
  }
}

#endif  // !MENON_BITS_EXPLODE_HH_
