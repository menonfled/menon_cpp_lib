/// @file   menon/bits/sync_object.hh
/// @author @menonfled
/// ライブラリ内で使用する同期オブジェクトの定義
#ifndef MENON_BITS_SYNC_OBJECT_HH_
#define MENON_BITS_SYNC_OBJECT_HH_
#pragma once

#include <mutex>

namespace menon
{
  namespace detail
  {
    inline std::mutex sync_object;
  }
}

#endif  // !MENON_BITS_SYNC_OBJECT_HH_
