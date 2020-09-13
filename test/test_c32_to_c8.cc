#include "menon/encoding.hh"
#include <boost/core/lightweight_test.hpp>
#include <algorithm>
#include <iconv.h>
#include <cstdio>

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

  // std::fprintf(stderr, "c32 = U+%08x\n", c32);
  if (auto cd = iconv_open("utf-8", "utf-32LE"))
  {
    iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft);
    iconv_close(cd);
  }
  else
  {
    std::perror("fail:");
  }

  char8_t c8[8];
  auto n =  menon::c32_to_c8(c32, c8, 8);

  BOOST_TEST(std::equal(c8 + 0, c8 + n, utf8 + 0, utf8 + n));
}

int main()
{
  for (char32_t c32 = 0; c32 <= 0x0ffff; c32++)
  {
    if ((0xd800 <= c32 && c32 <= 0xdbff) || (0xdc00 <= c32 && c32 <= 0xdfff))
      continue;
    test(c32);
  }
  return boost::report_errors();
}