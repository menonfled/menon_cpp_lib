/// @file   menon/bits/puts/hh
/// puts系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_PUTS_HH_
#define MENON_BITS_PUTS_HH_
#pragma once

#include "menon/bits/mb_convert_encoding.hh"
#include <cstdio>
#include <ostream>
#include <type_traits>

namespace menon
{
  namespace detail
  {
    template <char Delimiter = '\0'>
    auto puts_raw(std::string_view sv, std::FILE* stream)
    {
      Expects(stream != nullptr);
      flockfile(stream);
      auto _ = gsl::finally([stream] {
        funlockfile(stream);
      });

      for (auto c : sv)
      {
        if (putc_unlocked(c, stream) < 0)
          return EOF;
      }
      if constexpr (Delimiter)
      {
        if (putc_unlocked(Delimiter, stream) < 0)
          return EOF;
      }
      return 0;
    }

    template <char Delimiter = '\0'>
    auto puts_raw(std::string_view sv, std::ostream& os)
    {
      std::ostream::sentry x(os);
      if (x)
      {
      for (auto c : sv)
      {
        if (!os.put(c))
          return EOF;
      }
      if constexpr (Delimiter)
      {
        if (!os.put(Delimiter))
          return EOF;
      }
      }
      return 0;
    }

    template <char Delimiter, typename Char, typename Traits, typename Stream>
    auto puts_helper(std::basic_string_view<Char, Traits> sv, Stream& stream)
    {
      std::string buf;
      auto to_encoding = mb_external_encoding();
      if constexpr (std::is_same_v<Char, char>)
      {
        auto from_encoding = get_internal_encoding<Char>();
        if (from_encoding == to_encoding)
          return puts_raw(sv, stream);
        buf = mb_convert_encoding(sv, to_encoding, from_encoding);
      }
      buf = mb_convert_encoding<char>(sv, to_encoding);
      return puts_raw(buf, stream);
    }
  }

  /// ストリームに1行書き込む
  /// @param[in]  s       書き込む文字列
  /// @param[in]  stream  ストリーム
  /// @return     成功時は0を、失敗時はEOFを返す。
  /// 標準関数のputs関数と同様だが以下の点が異なる。
  ///
  /// - 標準出力以外のストリームを指定できる。
  /// - char型のナル終端文字列以外を指定できる。
  template <typename String>
  auto puts(String const& s, std::FILE* stream = stdout)
  {
    using ::menon::sv;
    return detail::puts_helper<'\n'>(sv(s), stream);
  }

  /// ストリームに1行書き込む
  /// @param[in]  s       書き込む文字列
  /// @param[in]  os      出力ストリーム
  /// @return     成功時は0を、失敗時はEOFを返す。
  /// 標準関数のputs関数と同様だが以下の点が異なる。
  ///
  /// - 出力先にostreamを指定できる。
  /// - char型のナル終端文字列以外を指定できる。
  template <typename String>
  auto puts(String const& s, std::ostream& os)
  {
    using ::menon::sv;
    return detail::puts_helper<'\n'>(sv(s), os);
  }
}

#endif  // !MENON_BITS_PUTS_HH_
