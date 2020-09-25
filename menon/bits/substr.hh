/// @file   menon/bits/substr.hh
/// substr系関数の定義
/// @author menonfled
#ifndef MENON_BITS_SUBSTR_HH_
#define MENON_BITS_SUBSTR_HH_

#include "menon/bits/sv.hh"
#include <cstdint>

namespace menon
{
  /// 部分文字列の取得
  /// @param[in]  s     元の文字列
  /// @param[in]  pos   部分文字列の開始位置
  /// @param[in]  n     部分文字列の長さ
  /// @return     sのうち区間[pos, pos+n)にあたる部分文字列を返す。
  /// @throw      posにsの範囲外の値を指定した場合はout_of_range例外を送出する。
  /// @attention  pos+nがsの長さより大きい場合はsの長さまで切り詰める。
  template <typename String>
  constexpr auto substr(String const& s, std::size_t pos, std::size_t n = SIZE_MAX)
  {
    using ::menon::sv;
    return sv(s).substr(pos, n);
  }

  /// 左端部分文字列の取得
  /// @param[in]  s     元の文字列
  /// @param[in]  n     部分文字列の長さ
  /// @return     sのうち区間[0, pos+n)にあたる部分文字列を返す。
  /// @attention  pos+nがsの長さより大きい場合はsの長さまで切り詰める。
  template <typename String>
  constexpr auto left(String const& s, std::size_t n)
  {
    return substr(s, 0, n);
  }

  /// 右端左端部分文字列の取得
  /// @param[in]  s     元の文字列
  /// @param[in]  n     部分文字列の長さ
  /// @return     sのうち区間[s.size()-n, s.size())にあたる部分文字列を返す。
  /// @attention  nがsの長さより大きい場合はsを返す。
  template <typename String>
  constexpr auto right(String const& s, std::size_t n)
  {
    using ::menon::sv;
    auto t = sv(s);
    auto length = t.size();
    if (n > length)
      n = length;
    auto pos = length - n;
    return t.substr(pos, n);
  }
}

#endif  // !MENON_BITS_SUBSTR_HH_