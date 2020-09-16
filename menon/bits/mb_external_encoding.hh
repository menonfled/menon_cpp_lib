/// @file   menon/bits/mb_external_encoding.hh
/// @author @menonfled
/// mb_external_encoding関数の定義
#ifndef MENON_BITS_MB_EXTERENAL_ENCODING_HH_
#define MENON_BITS_MB_EXTERENAL_ENCODING_HH_
#pragma once

#include "menon/bits/encoding_list.hh"

namespace menon
{
  /// 外部文字エンコーディングの設定および取得を行う。
  /// @param[in]  encoding  エンコーディング文字列またはnullptr
  /// @return     設定されているエンコーディング文字列を返す。呼び出しに失敗した場合はnullptrを返す。
  /// encodingにnullptr以外を指定した場合、外部文字エンコーディングをその値に設定する。
  /// encodingにnullptrを指定した場合は設定は行わない。
  inline auto mb_external_encoding(char const* encoding = nullptr)
    -> const char*
  {
    static thread_local int _ = detail::default_encoding_key;

    auto r = _;
    if (r < 0)
      r = detail::default_encoding_key;
    if (encoding)
    {
      auto key = detail::find_encoding_key(encoding);
      if (key < 0)
        return nullptr;
      _ = key;
    }
    return detail::encoding_list[r];
  }
}

#endif  // !MENON_BITS_MB_EXTERENAL_ENCODING_HH_
