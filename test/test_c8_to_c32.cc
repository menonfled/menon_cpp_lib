// test_c8_to_c32.c
#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <algorithm>
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
    char8_t utf8[4];
    char outbuf[8] = {};
  };
  char* p_inbuf = inbuf;
  char* p_outbuf = outbuf;
  size_t inbyteleft = 8;
  size_t outbyteleft = 8;

  utf32 = c32;

  // UTF-32LEからUTF-8に変換し、比較対象のデータを作る。
  if (auto cd = iconv_open("utf-8", "utf-32LE"))
  {
    iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft);
    iconv_close(cd);
  }
  else
  {
    std::perror("fail:");
  }

  // UTF-8からUTF-32へ変換する。
  auto n = menon::c8_to_c32(utf8, 4, &utf32);

  // c8_to_c32関数は1以上を返すはず
  BOOST_TEST_GT(n, 0);
  // c8_to_c32関数で変換した結果とiconvで得た比較対象のUTF-8は等しいはず
  BOOST_TEST_EQ((int)utf32, (int)c32);
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
