// test_c32_to_c16.cc
#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <iconv.h>
#include <cstdio>

// UTF-32の1文字についてのテストコード
void test(char32_t c32)
{
  union
  {
    char32_t utf32;
    char inbuf[8] = {};
  };
  union
  {
    char16_t utf16[2];
    char outbuf[8] = {};
  };
  char* p_inbuf = inbuf;
  char* p_outbuf = outbuf;
  size_t inbyteleft = 8;
  size_t outbyteleft = 8;

  utf32 = c32;

  // UTF-32LEからUTF-16LEに変換し、比較対象のデータを作る。
  if (auto cd = iconv_open("utf-16LE", "utf-32LE"))
  {
    iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft);
    iconv_close(cd);
  }
  else
  {
    std::perror("fail:");
  }

  // UTF-32からUTF-16への変換
  char16_t c16[8];
  auto n = menon::c32_to_c16(c32, c16, 8);

  // 変換後のUTF-16の長さは1以上
  BOOST_TEST_GE(n, 1);

  // 最初の要素を比較
  BOOST_TEST_EQ((int)c16[0], (int)utf16[0]);

  // サロゲートペアの場合
  if (n > 1)
    BOOST_TEST_EQ((int)c16[1], (int)utf16[1]);
}

int main()
{
  // 全種類の文字を総当たりする。
  for (char32_t c32 = 0; c32 <= 0x0ffff; c32++)
  {
    if ((0xd800 <= c32 && c32 <= 0xdbff) || (0xdc00 <= c32 && c32 <= 0xdfff))
      continue;
    test(c32);
  }
  return boost::report_errors();
}
