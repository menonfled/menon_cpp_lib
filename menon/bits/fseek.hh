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

namespace menon
{
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
}

#endif  // !MENON_BITS_FSEEK_HH_
