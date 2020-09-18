/// @file   menon/bits/mb_internal_encoding.hh
/// @author @menonfled
/// mb_internal_encoding関数の定義
#ifndef MENON_BITS_MB_INTERNAL_ENCODING_HH_
#define MENON_BITS_MB_INTERNAL_ENCODING_HH_
#pragma once

#include "menon/bits/encoding_list.hh"

namespace menon
{
  /// 内部文字エンコーディングの設定および取得を行う。
  /// @param[in]  encoding  エンコーディング文字列またはnullptr
  /// @return     設定されているエンコーディング文字列を返す。呼び出しに失敗した場合はnullptrを返す。
  /// encodingにnullptr以外を指定した場合、内部文字エンコーディングをその値に設定する。
  /// encodingにnullptrを指定した場合は設定は行わない。
  ///
  /// この関数はPHPからの借用だが、成功時はtrueではなく以前に設定されていたエンコーディング文字列を、
  /// 失敗時はfalseではなくnullptrを返す点に注意
  inline auto mb_internal_encoding(char const* encoding = nullptr)
    -> char const*
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

  /// 文字型に対応する内部文字エンコーディングの取得
  /// @return   内部文字エンコーディングを返す。
  template <typename Char>
  char const* get_internal_encoding();

  template <>
  constexpr char const* get_internal_encoding<char32_t>()
  {
  #if defined(_MSC_VER) || __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return detail::encoding_list[detail::find_encoding_key("UTF-32LE")];
  #else
    return detail::encoding_list[detail::find_encoding_key("UTF-32BE")];
  #endif
  }

  template <>
  constexpr char const* get_internal_encoding<char16_t>()
  {
  #if defined(_MSC_VER) || __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return detail::encoding_list[detail::find_encoding_key("UTF-16LE")];
  #else
    return detail::encoding_list[detail::find_encoding_key("UTF-16BE")];
  #endif
  }

  template <>
  constexpr char const* get_internal_encoding<char8_t>()
  {
    return detail::encoding_list[detail::find_encoding_key("UTF-8")];
  }

  template <>
  constexpr char const* get_internal_encoding<wchar_t>()
  {
    if (sizeof(wchar_t) == 2)
      return get_internal_encoding<char16_t>();
    else if (sizeof(wchar_t) == 4)
      return get_internal_encoding<char32_t>();
    return mb_internal_encoding();
  }

  template <>
  inline char const* get_internal_encoding<char>()
  {
    return mb_internal_encoding();
  }

  template <>
  inline char const* get_internal_encoding<signed char>()
  {
    return mb_internal_encoding();
  }

  template <>
  inline char const* get_internal_encoding<unsigned char>()
  {
    return mb_internal_encoding();
  }
}

#endif  // !MENON_BITS_MB_INTERNAL_ENCODING_HH_
