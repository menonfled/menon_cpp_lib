/// @file   menon/bits/mb_convert_encoding.hh
/// mb_convert_encoding関数の定義
/// @author @menonleft
#ifndef MENON_BITS_MB_CONVERT_ENCODING_HH_
#define MENON_BITS_MB_CONVERT_ENCODING_HH_
#pragma once

#include "menon/bits/sv.hh"
#include "menon/bits/mb_internal_encoding.hh"
#include "menon/bits/mb_external_encoding.hh"
#include <stdexcept>
#include <memory>
#include <string_view>
#include <string>
#include <type_traits>
#include <cstring>
#include <cerrno>
#include <iconv.h>

namespace menon
{
  namespace detail
  {
    template <typename ToChar, typename FromChar, typename Traits>
    auto mb_convert_encoding_helper(std::basic_string_view<FromChar, Traits> sv, char const* to_encoding, char const* from_encoding)
      -> std::basic_string<ToChar>
    {
      if (sizeof(ToChar) == sizeof(FromChar) && (to_encoding == from_encoding || std::strcmp(to_encoding, from_encoding) == 0))
        return { reinterpret_cast<ToChar const*>(sv.data()), sv.size() };

      if (auto cd = iconv_open(to_encoding, from_encoding))
      {
        std::size_t inbyteleft = sv.size() * sizeof(FromChar);
        char* p_inbuf = const_cast<char*>(reinterpret_cast<char const*>(sv.data()));
        constexpr std::size_t outbufsize = 1024;
        std::string r;
        r.reserve(outbufsize);

        while (inbyteleft > 0)
        {
          char outbuf[outbufsize];
          std::size_t outbyteleft = outbufsize;
          char* p_outbuf = outbuf;

          errno = 0;
          if (iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft) == std::size_t(-1))
            throw std::invalid_argument(std::string("menon::mb_convert_encoding: ") + std::strerror(errno));
          r.append(outbuf, outbufsize - outbyteleft);
        }
        iconv_close(cd);
        if constexpr (std::is_same_v<ToChar, char>)
          return r;
        else
          return { reinterpret_cast<ToChar const*>(r.data()), r.size() / sizeof(ToChar) };
      }
      throw std::invalid_argument("menon::mb_convert_encoding");
    }
  }

  /// 文字列のエンコーディングを変換する。
  /// @param[in]  sv            変換対象の文字列
  /// @param[in]  to_encoding   変換先エンコーディング
  /// @param[in]  from_encoding 変換後エンコーディング
  /// この関数はPHPの同名の関数からの借用である。
  /// ただし、現状の実装ではfrom_encodingに指定できるエンコーディングはひとつのみである。
  inline auto mb_convert_encoding(std::string_view sv, char const* to_encoding, char const* from_encoding = mb_internal_encoding())
    -> std::string
  {
    return detail::mb_convert_encoding_helper<char>(sv, to_encoding, from_encoding);
  }

  /// 文字列のエンコーディングを変換する。
  /// @param[in]  sv            変換対象の文字列
  /// @param[in]  to_encoding   変換先エンコーディング
  /// この関数を呼び出す際は、返却値の文字型をテンプレート実引数として明示的に指定すること。
  template <typename Char, typename T>
  inline auto mb_convert_encoding(T s, char const* to_encoding = get_internal_encoding<Char>())
  {
    using ::menon::sv;
    auto t = sv(s);
    using from_char_type = typename decltype(t)::value_type;
    return detail::mb_convert_encoding_helper<Char>(t, to_encoding, get_internal_encoding<from_char_type>());
  }

  /// バイト列のエンコーディングを変換した文字列を生成する。
  /// @param[in]  bytes         変換対象のバイト列
  /// @param[in]  to_encoding   変換先エンコーディング
  /// @param[in]  from_encoding 変換後エンコーディング
  template <typename Char>
  inline auto mb_convert_encoding(std::byte const* bytes, std::size_t n, char const* to_encoding, char const* from_encoding)
    -> std::string
  {
    return detail::mb_convert_encoding_helper<Char>(sv(bytes, n), to_encoding, from_encoding);
  }
}

#endif  // !MENON_BITS_MB_CONVERT_ENCODING_HH_
