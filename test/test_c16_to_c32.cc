// tes_c16_to_c32.cc
#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <algorithm>
#include <iconv.h>
#include <cstdio>

// UTF-16の1文字についてのテストコード
void test(char16_t const* c16, std::size_t n)
{
  union
  {
    char32_t utf32;
    char outbuf[8] = {};
  };
  union
  {
    char16_t utf16[2];
    char inbuf[8] = {};
  };
  char* p_inbuf = inbuf;
  char* p_outbuf = outbuf;
  size_t inbyteleft = 8;
  size_t outbyteleft = 8;

  std::copy(c16, c16 + n, utf16);

  // UTF-16LEからUTF-32LEへ変換し、比較対象のデータを作る。
  if (auto cd = iconv_open("utf-32LE", "utf-16LE"))
  {
    iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft);
    iconv_close(cd);
  }
  else
  {
    std::perror("fail:");
  }

  char16_t s[8];
  std::copy(c16, c16 + n, s);
  char32_t c32 = 0;

  // UTF-16からUTF-32への変換
  n = menon::c16_to_c32(s, n, &c32);
  BOOST_TEST_EQ((int)c32, (int)utf32);

  // BMPの場合
  if (n == 1)
  {
    // UTF-16からUTF-32への変換
    c32 = menon::c16_to_c32(c16[0]);
    BOOST_TEST_EQ((int)c32, (int)utf32);
  }
}

int main()
{
  // BMP全種類の文字を総当たりする。
  for (int i = 0; i < 0x10000; i++)
  {
    char16_t c16 = (char16_t)i;
    if ((0xd800 <= c16 && c16 <= 0xdbff) || (0xdc00 <= c16 && c16 <= 0xdfff))
      continue;
    // std::printf("U+%04x\n", c16); std::fflush(stdout);
    char16_t s[2] = { c16 };
    std::size_t n = 1;
    test(s, n);
  }
  // サロゲートペア全種類の文字を総当たりする。
  for (int i = 0xd800; i <= 0xdbff; i++)
  {
    for (int j = 0xdc00; j <= 0xdfff; j++)
    {
      char16_t s[2] = { (char16_t)i, (char16_t)j };
      std::size_t n = 2;
      test(s, n);
    }
  }
  return boost::report_errors();
}
