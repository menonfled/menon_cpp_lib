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
#include <iterator>

namespace menon
{
  constexpr int FILE_APPEND = 0x1;

  /// ストリームにデータを書き込む
  /// @param[in]  stream      ストリーム
  /// @param[in]  data        書き込むデータ
  /// @return     書き込んだバイト数を返す。
  /// @attention  テンプレート引数TはPOD型であること
  template <typename C>
  inline auto stream_put_contents(std::FILE* stream, C const& data)
    -> decltype(std::data(data), std::size_t())
  {
    using value_type = std::remove_cv_t<std::remove_reference_t<decltype(*std::data(data))>>;
    static_assert(std::is_standard_layout_v<value_type> && std::is_trivially_copyable_v<value_type>);
    Expects(stream != nullptr);
    return std::fwrite(std::data(data), 1, sizeof(value_type) * std::size(data), stream);
  }

  /// 出力ストリームにデータを書き込む
  /// @param[in]  os          出力ストリーム
  /// @param[in]  data        書き込むデータ
  /// @return     書き込んだバイト数を返す。
  /// @attention  テンプレート引数TはPOD型であること
  template <typename C>
  inline auto stream_put_contents(std::ostream& os, C const& data)
    -> decltype(std::data(data), std::size_t())
  {
    using value_type = std::remove_cv_t<std::remove_reference_t<decltype(*std::data(data))>>;
    static_assert(std::is_standard_layout_v<value_type> && std::is_trivially_copyable_v<value_type>);
    Expects(os.good());
    return os.rdbuf()->sputn(reinterpret_cast<char const*>(std::data(data)), sizeof(value_type) * data.size());
  }

  /// ファイルにデータを書き込む
  /// @param[in]  path      書き込み先のパス
  /// @param[in]  data      書き込むデータ
  /// @param[in]  flags     フラグ（現在はFILE_APPENDのみ指定可）
  /// @return     書き込んだバイト数を返す。
  /// @throw      ファイルをオープンできないときはruntime_errorを送出する。
  /// @attention  テンプレート引数TはPOD型であること
  /// PHPの同名関数と同様であるが以下の点が異なる。
  ///
  /// - flagsにはFILE_APPENDのみ指定できる。
  /// - contextは指定不可
  ///
  /// FILE_APPENDを指定した場合、既存のファイルに追記する。
  template <typename C>
  auto file_put_contents(std::filesystem::path const& path, C const& data, int flags = 0)
    -> decltype(std::data(data), std::size_t())
  {
    using value_type = std::remove_cv_t<std::remove_reference_t<decltype(*std::data(data))>>;
    static_assert(std::is_standard_layout_v<value_type> && std::is_trivially_copyable_v<value_type>);
    char const* omode = "wb";
    if (flags & FILE_APPEND)
      omode = "ab";
    auto stream = std::fopen(path.string().c_str(), omode);
    if (stream == nullptr)
      throw std::runtime_error("menon::file_put_contents");

    auto _ = gsl::finally([stream] {
      std::fclose(stream);
    });
    return stream_put_contents(stream, data);
  }
}

#endif  // !MENON_BITS_FILE_PUT_CONTENTS_HH_
