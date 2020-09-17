/// @file   menon/bits/mb_convert_encoding.hh
/// @author @menonleft
/// mb_convert_encoding関数の定義
#ifndef MENON_BITS_MB_CONVERT_ENCODING_HH_
#define MENON_BITS_MB_CONVERT_ENCODING_HH_
#pragma once

#include "menon/bits/mb_internal_encoding.hh"
#include "menon/bits/mb_external_encoding.hh"
#include <stdexcept>
#include <memory>
#include <string_view>
#include <string>
#include <cstring>
#include <cerrno>
#include <iconv.h>

namespace menon
{
  /// 文字列のエンコーディングを変換する。
  /// @param[in]  sv            変換対象の文字列
  /// @param[in]  to_encoding   変換先エンコーディング
  /// @param[in]  from_encoding 変換後エンコーディング
  /// この関数はPHPの同名の関数からの借用である。
  /// ただし、現状の実装ではfrom_encodingに指定できるエンコーディングはひとつのみである。
  inline auto mb_convert_encoding(std::string_view sv, char const* to_encoding, char const* from_encoding = mb_internal_encoding())
    -> std::string
  {
    if (std::strcmp(to_encoding, from_encoding) == 0)
      return { sv.data(), sv.size() };

    if (auto cd = iconv_open(to_encoding, from_encoding))
    {
      std::size_t outbufsize = sv.size() * 4;
      std::size_t inbyteleft = sv.size();
      std::size_t outbyteleft = outbufsize;
      auto outbuf = std::make_unique<char[]>(outbufsize);
      char* p_inbuf = const_cast<char*>(sv.data());
      char* p_outbuf = outbuf.get();

      errno = 0;
      if (iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft) == std::size_t(-1))
        throw std::invalid_argument(std::string("menon::mb_convert_encoding: ") + std::strerror(errno));
      iconv_close(cd);
      return { outbuf.get(), outbufsize - outbyteleft };
    }
    throw std::invalid_argument("menon::mb_convert_encoding");
  }
}

#endif  // !MENON_BITS_MB_CONVERT_ENCODING_HH_
