/// @file   menon/bits/gets.hh
/// gets系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_GETS_HH_
#define MENON_BITS_GETS_HH_
#pragma once

#include "menon/encoding.hh"
#include <istream>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <utility>

namespace menon
{
  namespace detail
  {
    template <bool KeepDelimiter, char Delimiter = '\n'>
    auto gets_raw(std::string& buf, std::FILE* stream, int n)
      -> bool
    {
      flockfile(stream);
      auto _ = gsl::finally([stream] {
        funlockfile(stream);
      });

      while (!std::feof(stream))
      {
        if (n >= 0 && static_cast<int>(buf.size()) >= n)
          break;

        auto c = getc_unlocked(stream);
        if (c == EOF)
          break;
        if (c == Delimiter)
        {
          if constexpr (KeepDelimiter)
            buf.push_back(char(c));
          break;
        }
        buf.push_back(char(c));
      }
      return !std::ferror(stream);
    }

    template <bool KeepDelimiter, char Delimiter = '\n'>
    auto gets_raw(std::string& buf, std::istream& is, int n)
      -> bool
    {
      std::istream::sentry x(is);
      if (x)
      {
        while (is)
        {
          if (n >= 0 && static_cast<int>(buf.size()) >= n)
            break;

          char c;
          is.get(c);
          if (c == Delimiter)
          {
            if constexpr (KeepDelimiter)
            {
              buf.push_back(c);
            }
            break;
          }
          buf.push_back(c);
        }
      }
      return !is.bad();
    }

    template <bool KeepDelimiter, char Delimiter, typename Char, typename Stream>
    auto gets_helper(std::basic_string<Char>& s, Stream& stream, int n = -1)
      -> bool
    {
      if (n == 0)
      {
        s.clear();
        return true;
      }

      std::string buf;
      buf.reserve(256);
      if (!detail::gets_raw<KeepDelimiter, Delimiter>(buf, stream, n))
        return false;
      auto to_encoding = get_internal_encoding<Char>();
      auto from_encoding = mb_external_encoding();
      if constexpr (std::is_same_v<Char, char>)
      {
        if (to_encoding == from_encoding || std::strcmp(to_encoding, from_encoding) == 0)
        {
          s.swap(buf);
          return true;
        }
      }
      using ::menon::sv;
      s = mb_convert_encoding<Char>(sv(buf), to_encoding);
      return true;
    }
  }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       配列sの要素数
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - 標準入力以外のストリームを指定できる。
  /// - 格納先配列の要素数を指定できる。
  /// - 格納先にchar型以外のポインタを指定できる。
  ///
  /// 1行の長さがnより大きい場合は格納できない文字を捨てる。
  template <typename Char>
  auto gets(Char* s, int n, std::FILE* stream = stdin)
    -> Char*
  {
    Expects(s != nullptr);
    Expects(n >= 0);
    Expects(stream != nullptr);

    if (n == 0)
      return s;

    std::basic_string<Char> buf;
    if (detail::gets_helper<false, '\n'>(buf, stream))
    {
      n = std::min(static_cast<int>(buf.size()), n - 1);
      buf.copy(s, n);
      s[n] = {};
      return s;
    }
    return  nullptr;
 }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - 標準入力以外のストリームを指定できる。
  /// - 格納先配列の要素数までしか書き込まれない。
  /// - 格納先にchar型以外の配列を指定できる。
  ///
  /// 1行の長さがnより大きい場合は格納できない文字を捨てる。
  template <typename Char, std::size_t N>
  inline auto gets(Char (&s)[N], std::FILE* stream = stdin)
  {
    return gets(s, N, stream);
  }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  template <typename Char, typename Traits, typename Allocator>
  auto gets(std::basic_string<Char, Traits, Allocator>& s, std::FILE* stream = stdin)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    Expects(stream != nullptr);

    std::basic_string<Char> buf;
    if (!detail::gets_helper<false, '\n'>(buf, stream))
      throw std::invalid_argument("menon::gets");
    if constexpr (std::is_same_v<std::basic_string<Char, Traits, Allocator>, std::basic_string<Char>>)
      s.swap(buf);
    else
      s.assign(buf.cbegin(), buf.cend());
    return s;
 }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       配列sの要素数
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - istreamを指定する。
  /// - 格納先配列の要素数を指定できる。
  ///
  /// 1行の長さがnより大きい場合は格納できない文字を捨てる。
  template <typename Char>
  auto gets(Char* s, int n, std::istream& stream)
    -> Char*
  {
    Expects(s != nullptr);
    Expects(n >= 0);

    if (n == 0)
      return s;

    std::basic_string<Char> buf;
    if (detail::gets_helper<false, '\n'>(buf, stream))
    {
      n = std::min(static_cast<int>(buf.size()), n - 1);
      buf.copy(s, n);
      s[n] = {};
      return s;
    }
    return  nullptr;
 }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - istreamを指定する。
  /// - 格納先配列の要素数までしか書き込まれない。
  ///
  /// 1行の長さがnより大きい場合は格納できない文字を捨てる。
  template <typename Char, std::size_t N>
  inline auto gets(Char (&s)[N], std::istream& stream)
  {
    return gets(s, N, stream);
  }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  template <typename Char, typename Traits, typename Allocator>
  auto gets(std::basic_string<Char, Traits, Allocator>& s, std::istream& stream)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    std::basic_string<Char> buf;
    if (!detail::gets_helper<false, '\n'>(buf, stream))
      throw std::runtime_error("menon::gets");
    if constexpr (std::is_same_v<std::basic_string<Char, Traits, Allocator>, std::basic_string<Char>>)
      s.swap(buf);
    else
      s.assign(buf.cbegin(), buf.cend());
    return s;
 }




















  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       配列sの要素数
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のfgets関数と同様だが以下の点が異なる。
  ///
  /// - 標準入力以外のストリームを指定できる。
  template <typename Char>
  auto fgets(Char* s, int n, std::FILE* stream)
    -> Char*
  {
    Expects(s != nullptr);
    Expects(n >= 0);
    Expects(stream != nullptr);

    if (n == 0)
      return s;

    std::basic_string<Char> buf;
    if (detail::gets_helper<true, '\n'>(buf, stream, n - 1))
    {
      n = std::min(static_cast<int>(buf.size()), n - 1);
      buf.copy(s, n);
      s[n] = {};
      return s;
    }
    return  nullptr;
  }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       sに格納する最大の文字数
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  template <typename Char, typename Traits, typename Allocator>
  auto fgets(std::basic_string<Char, Traits, Allocator>& s, int n, std::FILE* stream)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    Expects(n >= 0);
    Expects(stream != nullptr);

    if (n == 0)
    {
      s.clear();
      return s;
    }

    std::basic_string<Char> buf;
    if (!detail::gets_helper<true, '\n'>(buf, stream, n))
      throw std::invalid_argument("menon::gets");
    if constexpr (std::is_same_v<std::basic_string<Char, Traits, Allocator>, std::basic_string<Char>>)
      s.swap(buf);
    else
      s.assign(buf.cbegin(), buf.cend());
    return s;
 }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       配列sの要素数（n >= 0）
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  /// 標準関数のgets関数と同様だが以下の点が異なる。
  ///
  /// - istreamを指定する。
  template <typename Char>
  auto fgets(Char* s, int n, std::istream& stream)
    -> Char*
  {
    Expects(s != nullptr);
    Expects(n >= 0);

    if (n == 0)
      return s;

    std::basic_string<Char> buf;
    if (detail::gets_helper<true, '\n'>(buf, stream))
    {
      n = std::min(static_cast<int>(buf.size()), n - 1);
      buf.copy(s, n);
      s[n] = {};
      return s;
    }
    return  nullptr;
 }

  /// ストリームから1行読み込む
  /// @param[in]  s       入力した文字列の格納先
  /// @param[in]  n       sに格納する最大の文字数（n >= 0）
  /// @param[in]  stream  ストリーム
  /// @return     sを返す。
  template <typename Char, typename Traits, typename Allocator>
  auto fgets(std::basic_string<Char, Traits, Allocator>& s, int n, std::istream& stream)
    -> std::basic_string<Char, Traits, Allocator>&
  {
    std::basic_string<Char> buf;
    if (!detail::gets_helper<true, '\n'>(buf, stream, n))
      throw std::runtime_error("menon::gets");
    if constexpr (std::is_same_v<std::basic_string<Char, Traits, Allocator>, std::basic_string<Char>>)
      s.swap(buf);
    else
      s.assign(buf.cbegin(), buf.cend());
    return s;
 }
}

#endif  // !MENON_BITS_GETS_HH_
