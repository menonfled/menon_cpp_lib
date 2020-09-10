/// @file   menon/demangle.hh
/// @author @menonfled
/// 型名のデマングルを行う関数の定義
#ifndef MENON_DEMANGLE_HH_
#define MENON_DEMANGLE_HH_
#pragma once

#include <typeindex>
#if __GNUC__ || __CLANG__
# include <cxxabi.h>
# include <cstdlib>
# include <new>
# include <stdexcept>
#endif

namespace menon
{
  /// type_info::nameメンバー関数が返す型名をデマングルする。
  /// @param[in]  s   type_info::nameが返す型名
  /// @return     デマングルされた文字列をstring型で返す。 
#if __GNUC__ || __CLANG__
  inline auto demangle(char const* s)
  {
    int status;

    char* t = abi::__cxa_demangle(s, nullptr, nullptr, &status);
    if (t == nullptr)
    {
      if (status == -1)
        throw std::bad_alloc();
      throw std::invalid_argument("menon::demangle");
    }
    std::string r(t);
    std::free(t);
    return r;
  }
#else
  inline auto demangle(char const* s)
  {
    return std::string(s);
  }
#endif

  /// type_infoオブジェクトからデマングル済みの型名を取り出す。
  /// @param[in]  info    type_infoオブジェクトへの参照
  /// @return     デマングルされた文字列をstring型で返す。 
  inline auto type_name(std::type_info const& info)
  {
    return demangle(info.name());
  }
}

#endif  // !MENON_DEMANGLE_HH_
