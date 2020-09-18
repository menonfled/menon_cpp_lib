/// @file   menon/bits/gets.hh
/// @author @menonfled
/// gets関数の定義
#ifndef MENON_BITS_GETS_HH_
#define MENON_BITS_GETS_HH_
#pragma once

#include "menon/encoding.hh"
#include <istream>
#include <cstdio>
#include <stdexcept>
#include <string>

namespace menon
{
  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       配列sの要素数
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - 標準入力以外のストリームを指定できる。
  /// - 格納先配列の要素数を指定できる。
  ///
  /// 1行の長さがnより大きい場合は格納できない文字を捨てる。
  template <typename Char>
  auto gets(Char* s, int n, std::FILE* stream = stdin)
    -> Char*
  {
    if (s == nullptr || n < 1 || stream == nullptr)
      throw std::invalid_argument(__func__);

    std::string buf;
    buf.reserve(256);
    {
      flockfile(stream);
      auto _ = gsl::finally([stream] {
        funlockfile(stream);
      });

      while (!std::feof(stream))
      {
        auto c = getc_unlocked(stream);
        if (c == EOF || c == Char('\n'))
          break;
        buf.push_back(char(c));
      }
    }
    using ::menon::sv;
    auto t = mb_convert_encoding<Char>(sv(buf), mb_external_encoding());
    n = std::min(static_cast<int>(t.size()), n - 1);
    t.copy(s, n);
    s[n] = {};
    return s;
 }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - 標準入力以外のストリームを指定できる。
  /// - 格納先配列の要素数までしか書き込まれない。
  ///
  /// 1行の長さがnより大きい場合は格納できない文字を捨てる。
  template <typename Char, std::size_t N>
  inline auto gets(Char (&s)[N], std::FILE* stream = stdin)
  {
    return gets(s, N, stream);
  }
}

#endif  // !MENON_BITS_GETS_HH_

