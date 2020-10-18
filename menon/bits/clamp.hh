/// @file   menon/bits/clamp.hh
/// clamp系関数の定義
/// @author @menonfled
#ifndef MENON_BITS_CLAMP_HH_
#define MENON_BITS_CLAMP_HH_
#pragma once

#include "menon/bits/sv.hh"
#include <concepts>
#include <utility>

namespace menon
{
  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  template <typename T>
  constexpr auto clamp(T const& value, T const& low, T const& high)
  {
    Expects(low < high);
    return value < low ? low : (value > high ? high : value);
  }

  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  /// value, low, highは符号付き整数でなければならない。
  template <std::signed_integral T, std::signed_integral U, std::signed_integral V>
  constexpr auto clamp(T const& value, U const& low, V const& high)
  {
    return value < low ? low : (value > high ? high : value);
  }

  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  /// value, low, highは符号無し整数でなければならない。
  template <std::unsigned_integral T, std::unsigned_integral U, std::unsigned_integral V>
  constexpr auto clamp(T const& value, U const& low, V const& high)
  {
    return value < low ? low : (value > high ? high : value);
  }

  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  /// value, low, highは浮動小数点数でなければならない。
  template <std::floating_point T, std::floating_point U, std::floating_point V>
  constexpr auto clamp(T const& value, U const& low, V const& high)
  {
    return value < low ? low : (value > high ? high : value);
  }

  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  /// valueおよびlowは符号付き整数、highは整数でなければならない。
  template <std::floating_point T, std::floating_point U, std::integral V>
  constexpr auto clamp(T const& value, U const& low, V const& high)
  {
    return value < low ? low : (value > high ? high : value);
  }

  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  /// valueおよびhighは符号付き整数、lowは整数でなければならない。
  template <std::floating_point T, std::integral U, std::floating_point V>
  constexpr auto clamp(T const& value, U const& low, V const& high)
  {
    return value < low ? low : (value > high ? high : value);
  }

  /// 値を範囲内に収める。
  /// @param[in]  value     元の値
  /// @param[in]  low       範囲の下限
  /// @param[in]  high      範囲の上限
  /// @return     valueがlowより小さければlowを、highより大きければhighを、それ以外はvalueを返す。
  /// @attention  std::clampは参照を返すが、この関数は値を返すことに注意
  /// valueは符号付き整数、lowおよびhighは整数でなければならない。
  template <std::floating_point T, std::integral U, std::integral V>
  constexpr auto clamp(T const& value, U const& low, V const& high)
  {
    return value < low ? low : (value > high ? high : value);
  }
}

#endif  // !MENON_BITS_CLAMP_HH_
