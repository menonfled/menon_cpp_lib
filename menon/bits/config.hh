/// @file menon/bits/config.hh
/// 外部ライブラリのインストール状況の調査と各種設定
/// @author @menonfled
#ifndef MENON_BITS_CONFIG_HH_
#define MENON_BITS_CONFIG_HH_
#pragma once

// 現時点ではC++20以上のみを対象とする。
#if __cplusplus <= 201703L
# error Menon C++ Library requires C++20 compilation.
#endif

/// Windows用処理系の判定
#if defined(__MINGW32__) || defined(_MSC_VER)
# include "menon/bits/win_workaround.hh"
#endif

// Guidelines Support Libraryの判定
// バージョン番号を直接調べる方法方がないので、<gsl/span_ext>の有無を
// 調べて古いバージョンの使用を禁止する。
#if __has_include(<gsl/gsl>)
# include <gsl/gsl>
# if !__has_include(<gsl/span_ext>)
#   #error Guidelines Support Library is too old.
# endif
# define MENON_HAS_GSL   1
#else
# include <menon/bits/gsl_workaround.hh>
#endif

// Boost C++ Librariesの判定
#if __has_include(<boost/version.hpp>)
# include <boost/version.hpp>
# define MENON_HAS_BOOST 1
#endif

// Tcl/Tkの判定（ここではヘッダーファイルをインクルードしない）
#if __has_include(<tk.h>)
# define  MENON_HAS_TCLTK 1
#endif

#endif  // !MENON_BITS_CONFIG_HH_
