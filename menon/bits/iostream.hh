/// @file   menon/bits/iostream.hh
/// iostream関連の演算子関数の定義
/// @author @menonfled
#ifndef MENON_BITS_IOSTREAM_HH_
#define MENON_BITS_IOSTREAM_HH_
#pragma once

#include "menon/bits/mb_convert_encoding.hh"
#include <iostream>
#include <string>
#include <string_view>

namespace menon
{
  /// istreamおよびostreamに対する演算子関数提供用の名前空間
  inline namespace iostream_ops
  {
    /// UTF-8のostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, char8_t const* s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// UTF-16のostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, char16_t const* s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// UTF-32のostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, char32_t const* s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// ワイド文字列のostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, wchar_t const* s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u8stringのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::u8string const& s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u16stringのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::u16string const& s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u32stringのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::u32string const& s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// wstringのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::wstring const& s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u8string_viewのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::u8string_view s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u16string_viewのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::u16string_view s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u32string_viewのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::u32string_view s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// wstring_viewのostreamに対する出力
    /// @param[in,out]  os    出力ストリーム
    /// @param[in]      s     出力する文字列
    /// @return         osを返す。
    /// sをmb_internal_encodingで設定したエンコーディングに変換して出力する。
    inline std::ostream& operator<<(std::ostream& os, std::wstring_view s)
    {
      return os << mb_convert_encoding<char>(s, mb_internal_encoding());
    }

    /// u8stringへのistreamからの入力
    /// @param[in,out]  is    入力ストリーム
    /// @param[in]      s     入力した文字列の格納先
    /// @return         isを返す。
    inline std::istream& operator>>(std::istream& is, std::u8string& s)
    {
      std::string buf;
      is >> buf;
      s = mb_convert_encoding<char8_t>(buf, get_internal_encoding<char8_t>());
      return is;
    }

    /// u16stringへのistreamからの入力
    /// @param[in,out]  is    入力ストリーム
    /// @param[in]      s     入力した文字列の格納先
    /// @return         isを返す。
    inline std::istream& operator>>(std::istream& is, std::u16string& s)
    {
      std::string buf;
      is >> buf;
      s = mb_convert_encoding<char16_t>(buf, get_internal_encoding<char16_t>());
      return is;
    }

    /// u32stringへのistreamからの入力
    /// @param[in,out]  is    入力ストリーム
    /// @param[in]      s     入力した文字列の格納先
    /// @return         isを返す。
    inline std::istream& operator>>(std::istream& is, std::u32string& s)
    {
      std::string buf;
      is >> buf;
      s = mb_convert_encoding<char32_t>(buf, get_internal_encoding<char32_t>());
      return is;
    }

    /// wstringへのistreamからの入力
    /// @param[in,out]  is    入力ストリーム
    /// @param[in]      s     入力した文字列の格納先
    /// @return         isを返す。
    inline std::istream& operator>>(std::istream& is, std::wstring& s)
    {
      std::string buf;
      is >> buf;
      s = mb_convert_encoding<wchar_t>(buf, get_internal_encoding<wchar_t>());
      return is;
    }
  }
}

#endif  // !MENON_BITS_IOSTREAM_HH_
