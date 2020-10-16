/// @file   menon/bits/filelength.hh
/// filelength関数の定義
/// @author @menonfled
#ifndef MENON_BITS_FILELENGTH_HH_
#define MENON_BITS_FILELENGTH_HH_
#pragma once

#include "menon/bits/config.hh"
#include <cstdio>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>

// filelengthがマクロで定義されている場合の対策
#undef  filelength

namespace menon
{
  /// ファイルサイズの取得
  /// @param[in]  fd    ファイルディスクリプタ
  /// @return     成功時はファイルサイズを返す。失敗時は負値を返しerrnoを設定する。
  inline auto filelength(int fd)
    -> off_t
  {
    struct stat t;
    if (fstat(fd, &t) < 0)
      return -1LL;
    return static_cast<long long>(t.st_size);
  }

  /// ファイルサイズの取得
  /// @param[in]  stream   ストリームへのポインタ
  /// @return     成功時はファイルサイズを返す。失敗時は負値を返しerrnoを設定する。
  inline auto filelength(std::FILE* stream)
  {
    Expects(stream);
    return filelength(fileno(stream));
  }

  /// ファイルサイズの取得
  /// @param[in]  path    パス名
  /// @return     成功時はファイルサイズを返す。失敗時は負値を返しerrnoを設定する。
  inline auto filelength(std::filesystem::path const& path)
  {
    struct stat t;
    if (stat(path.string().c_str(), &t) < 0)
      return -1LL;
    return static_cast<long long>(t.st_size);
  }

  /// ファイルサイズの取得
  /// @param[in]  path    パス名
  /// @return     成功時はファイルサイズを返す。失敗時は負値を返しerrnoを設定する。
  /// この関数はfilelengthのシノニムである。
  inline auto filesize(std::filesystem::path const& path)
  {
    return filelength(path);
  }
}

#endif  // !MENON_BITS_FILELENGTH_HH_

