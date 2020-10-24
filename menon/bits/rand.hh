/// @file   menon/bits/rand.hh
/// rand系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_RAND_HH_
#define MENON_BITS_RAND_HH_
#pragma once

#include "menon/bits/config.hh"
#include <random>
#include <bit>
#include <cstdint>

namespace menon
{
  /// rand関数が返す結果の上限
  constexpr int rand_max = 0x1fffffff;

  /// 疑似乱数の生成
  /// @return 疑似乱数を返す。
  /// xoshiro128+による疑似乱数を生成する。
  int rand()
  {
    thread_local uint32_t s[4] = { std::random_device()() };
    uint32_t const result = s[0] + s[3];

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= s[1] << 9;

    s[3] = std::rotl(s[3], 11);

    return static_cast<int>((result >> 3) & rand_max);
  }
}

#endif  // !MENON_BITS_RAND_HH_
