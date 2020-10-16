/// @file   menon/bits/file_put_contents.hh
/// file_put_contents系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_FILE_PUT_CONTENTS_HH_
#define MENON_BITS_FILE_PUT_CONTENTS_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <cstdio>
#include <type_traits>
#include <filesystem>
#include <ostream>
#include <span>

namespace menon
{
  constexpr int FILE_APPEND = 0x1;

  /// ストリームにデータを書き込む
  /// @param[in]  stream      ストリーム
  /// @param[in]  data        書き込むデータ
  /// @return     書き込んだバイト数を返す。
  /// @attention  テンプレート引数TはPOD型であること
  template <typename T>
  auto stream_put_contents(std::FILE* stream, std::span<T> data)
  {
    static_assert(std::is_standard_layout_v<T> && std::is_trivially_copyable_v<T>);
    Expects(stream != nullptr);
    return std::fwrite(data.data(), 1, sizeof(T) * data.size(), stream);
  }

  /// 出力ストリームにデータを書き込む
  /// @param[in]  os          出力ストリーム
  /// @param[in]  data        書き込むデータ
  /// @return     書き込んだバイト数を返す。
  /// @attention  テンプレート引数TはPOD型であること
  template <typename T>
  auto stream_put_contents(std::ostream& os, std::span<T> data)
  {
    static_assert(std::is_standard_layout_v<T> && std::is_trivially_copyable_v<T>);
    Expects(os.good());
    return os.rdbuf()->sputn(reinterpret_cast<char const*>(data.data()), sizeof(T) * data.size());
  }
}

#endif  // !MENON_BITS_FILE_PUT_CONTENTS_HH_
