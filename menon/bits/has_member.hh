/// @file   menon/bits/has_member.hh
/// MENON_DEFINE_HAS_MEMBERマクロの定義
/// @author @menonfled
#ifndef MENON_BITS_HAS_MEMBER_HH_
#define MENON_BITS_HAS_MEMBER_HH_
#pragma once

#include <type_traits>
#include <utility>

/// has_##memberメタ関数およびhas_##member##_v定数を定義するマクロ
#define MENON_DEFINE_HAS_MEMBER(member)   \
  namespace menon {   \
    template<typename C> struct has_##member {   \
        static std::false_type check(...);  \
        template<class T, int _ =(&T::member, 0)> static std::true_type  check(T*);  \
        static constexpr bool value = decltype(check(std::declval<C*>()))::value;   \
    };  \
    template<typename C> constexpr bool has_##member##_v = has_##member<C>::value;  \
  }

#endif  // !MENON_BITS_HAS_MEMBER_HH_
