﻿/// @file   menon/bits/win_workarond.hh
/// @author @menonfled
/// Windows用処理系で定義されないPOSIXまたはGLibc関数の代替定義
#ifndef MENON_BITS_WIN_WORKAROUND_HH_
#define MENON_BITS_WIN_WORKAROUND_HH_
#pragma once

#if defined(__MINGW32__) || defined(_MSC_VER)
#include <cstdio>

namespace menon
{
  inline void flockfile(FILE* stream)
  {
    ::_lock_file(stream);
  }

  inline void funlockfile(FILE* stream)
  {
    ::_unlock_file(stream);
  }

  inline int getc_unlocked(FILE* stream)
  {
    return _getc_nolock(stream);
  }

  inline int putc_unlocked(int c, FILE* stream)
  {
    return _putc_nolock(c, stream);
  }
}

#endif  // defined(__MINGW32__) || defined(_MSC_VER)

#endif  // !MENON_BITS_WIN_WORKAROUND_HH_
