/// @file   menon/bits/fseek.hh
/// fseekおよびftell関数の定義
/// @author @menonfled
#ifndef MENON_BITS_FSEEK_HH_
#define MENON_BITS_FSEEK_HH_
#pragma once

#include "menon/bits/config.hh"
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace menon
{
  namespace detail
  {
    inline auto whence(int dir)
    {
      std::ios_base::seekdir r;
      switch (dir)
      {
        case SEEK_SET:
          r = std::ios_base::beg;
          break;
        case SEEK_CUR:
          r = std::ios_base::cur;
          break;
        case SEEK_END:
          r = std::ios_base::end;
          break;
        default:
          throw std::invalid_argument("menon::fseek");
      }
      return r;
    }
  }

  /// 指定位置へのシーク
  /// @param[in]  stream    ストリーム
  /// @param[in]  offset    whenceからのオフセット位置
  /// @param[in]  whence    SEEK_SET, SEET_CUR, またはSEEK_END
  /// @return     0を返す。
  /// @throw      失敗時はruntime_error例外が発生する。
  /// 標準関数のfseekはlong型の表現範囲に依存する。
  /// long型が32ビットの場合、2Gバイトを超えるファイルには対応しない。
  /// 2Gバイトを超えるファイルに対応するシークは処理系によって異なる関数が定義されている。
  /// この関数はそうした処理間の差異を吸収することを目的とする。
  inline int fseek(std::FILE* stream, off_t offset, int whence)
  {
    Expects(stream != nullptr);
    errno = 0;
#ifdef _MSC_VER
    int r = _fseei64(stream, offset, whence);
#else
    int r = fseeko(stream, offset, whence);
#endif
    if (r < 0)
      throw std::runtime_error(std::strerror(errno));
    return 0;
  }

  /// 指定位置へのシーク
  /// @param[in]  is        入力ストリーム
  /// @param[in]  offset    whenceからのオフセット位置
  /// @param[in]  whence    SEEK_SET, SEET_CUR, またはSEEK_END
  /// @return     0を返す。
  /// @throw      失敗時はruntime_error例外が発生する。
  template <typename Char, typename Traits>
  inline int fseek(std::basic_istream<Char, Traits>& is, off_t offset, int whence)
  {
    is.seekg(offset, detail::whence(whence));
    if (is.bad())
      throw std::runtime_error("menon::fseek");
    return 0;
  }

  /// 指定位置へのシーク
  /// @param[in]  os        出力ストリーム
  /// @param[in]  offset    whenceからのオフセット位置
  /// @param[in]  whence    SEEK_SET, SEET_CUR, またはSEEK_END
  /// @return     0を返す。
  /// @throw      失敗時はruntime_error例外が発生する。
  template <typename Char, typename Traits>
  inline int fseek(std::basic_ostream<Char, Traits>& os, off_t offset, int whence)
  {
    os.seekp(offset, detail::whence(whence));
    if (os.bad())
      throw std::runtime_error("menon::fseek");
    return 0;
  }

  /// 指定位置へのシーク
  /// @param[in]  ios       入出力ストリーム
  /// @param[in]  offset    whenceからのオフセット位置
  /// @param[in]  whence    SEEK_SET, SEET_CUR, またはSEEK_END
  /// @return     0を返す。
  /// @throw      失敗時はruntime_error例外が発生する。
  template <typename Char, typename Traits>
  inline int fseek(std::basic_iostream<Char, Traits>& ios, off_t offset, int whence)
  {
    ios.seekg(offset, detail::whence(whence));
    ios.seekp(offset, detail::whence(whence));
    if (ios.bad())
      throw std::runtime_error("menon::fseek");
    return 0;
  }

  /// シーク位置の取得
  /// @param[in]  stream    入力ストリーム
  /// @return     現在のシーク位置を返す。
  /// @throw      失敗時はruntime_error例外が発生する。
  /// 標準関数のftellはlong型の表現範囲に依存する。
  /// long型が32ビットの場合、2Gバイトを超えるファイルには対応しない。
  /// 2Gバイトを超えるファイルに対応するシークは処理系によって異なる関数が定義されている。
  /// この関数はそうした処理間の差異を吸収することを目的とする。
  inline off_t ftell(std::FILE* stream)
  {
    Expects(stream != nullptr);
    errno = 0;
#ifdef _MSC_VER
    auto r = _ftelli64(stream);
#else
    auto r = ftello(stream);
#endif
    if (r < 0)
      throw std::runtime_error(std::strerror(errno));
    return r;
  }
}

#endif  // !MENON_BITS_FSEEK_HH_
