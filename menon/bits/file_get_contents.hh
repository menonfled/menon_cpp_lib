/// @file   menon/bits/file_get_contents.hh
/// file_get_contents系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_FILE_GET_CONTENTS_HH_
#define MENON_BITS_FILE_GET_CONTENTS_HH_
#pragma once

#include "menon/bits/filelength.hh"
#include "menon/bits/fseek.hh"
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <iterator>

namespace menon
{
  namespace detail
  {
    template <typename Result>
    auto stream_get_contents_helper(std::FILE* stream, off_t maxlength, off_t offset)
    {
      using value_type = typename Result::value_type;
      // is_podが非推奨になったので代替表現を使用
      static_assert(std::is_trivially_copyable_v<value_type> && std::is_standard_layout_v<value_type>);      
      Expects(stream != nullptr);

      auto n = filelength(stream);
      Expects(offset < n);
      if (offset >= 0)
        menon::fseek(stream, offset, SEEK_SET);
      offset = menon::ftell(stream);
      if (maxlength >= 0)
        n = std::min(n - offset, maxlength);
      else
        n -= offset;

      Result r;
      r.resize(n);
      std::size_t size = std::fread(std::data(r), sizeof(value_type), n, stream);
      r.resize(size);
      return r;
    }
  }

  /// 残りのストリームをコンテナに読み込む
  /// @param[in]  stream      ストリーム
  /// @param[in]  maxlength   読み込む最大要素数。負値の場合はファイルの末尾まで読み込む。
  /// @param[in]  offset      読み込みファイルの先頭位置。負値の場合は現在のシーク位置から読み込む。
  /// @return     読み込んだデータをvector<byte>で返す。
  inline auto stream_get_contents(std::FILE* stream, off_t maxlength = -1, off_t offset = -1)
    -> std::vector<std::byte>
  {
    return detail::stream_get_contents_helper<std::vector<std::byte>>(stream, maxlength, offset);
  }

  /// ファイルの内容をコンテナに読み込む
  /// @param[in]  path        読み込むファイルのパス
  /// @param[in]  maxlength   読み込む最大要素数。負値の場合はファイルの末尾まで読み込む。
  /// @param[in]  offset      読み込みファイルの先頭位置。負値の場合は先頭から読み込む。
  /// @return     読み込んだデータをvector<byte>で返す。
  /// @throw      pathがオープンできなければinvalid_argument例外を送出する。
  inline auto file_get_contents(std::filesystem::path const& path, off_t maxlength = -1, off_t offset = -1)
  {
    std::vector<std::byte> r;
    if (auto stream = std::fopen(path.string().c_str(), "rb"))
    {
      auto _ = gsl::finally([stream]() {
        std::fclose(stream);
      });
      r = stream_get_contents(stream, maxlength, offset);
    }
    else
    {
      throw std::invalid_argument("menon::file_get_contents");
    }
    return r;
  }
}

#endif  // !MENON_BITS_FILE_GET_CONTENTS_HH_
