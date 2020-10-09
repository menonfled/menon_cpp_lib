/// @file menon/bits/for_each_n.hh
/// 添え数を用いたfor_each関数の亜種の定義
/// @author @menonfled
#ifndef MENON_BITS_FOR_EACH_N_HH_
#define MENON_BITS_FOR_EACH_N_HH_
#pragma once

#include "menon/bits/config.hh"
#include <iterator>

namespace menon
{
  /// 添え数を用いたfor_each関数
  /// @param[in]  iter    操作対象の先頭位置を指す反復子
  /// @param[in]  n       操作対象の要素数
  /// @param[in]  pred    述語
  /// 区間[0, n)のiに対してpred(iter, i)を呼び出す。  
  template <std::forward_iterator Iterator, typename Size, typename Pred>
  auto for_each_n(Iterator iter, Size n, Pred pred)
  {
    for (Size i = 0; i < n; i++)
      pred(iter, i);
    return iter + n;
  }
}

#endif  // !MENON_BITS_FOR_EACH_N_HH_
