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
    char utf8_buf[8] = {};
  };
  union
  {
    char16_t utf16[2];
    char utf16_buf[8] = {};
  };

  utf32 = c32;

  if (auto cd = iconv_open("utf-16LE", "utf-32LE"))
  {
    char* p_inbuf = inbuf;
    char* p_outbuf = utf16_buf;
    size_t inbyteleft = 8;
    size_t outbyteleft = 8;
    iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft);
    iconv_close(cd);
  }
  else
  {
    std::perror("fail:");
  }

  if (auto cd = iconv_open("utf-8", "utf-32LE"))
  {
    char* p_inbuf = inbuf;
    char* p_outbuf = utf8_buf;
    size_t inbyteleft = 8;
    size_t outbyteleft = 8;
    iconv(cd, &p_inbuf, &inbyteleft, &p_outbuf, &outbyteleft);
    iconv_close(cd);
  }
  else
  {
    std::perror("fail:");
  }

  {
    char8_t c8[8];
    auto [n1, n2] = menon::c16_to_c8(utf16, 2, c8, 4);
    BOOST_TEST(std::equal(c8 + 0, c8 + n2, utf8 + 0, utf8 + n2));
  }
  {
    char16_t c16[2];
    auto [n1, n2] = menon::c8_to_c16(utf8, 4, c16, 2);
    BOOST_TEST(std::equal(c16 + 0, c16 + n2, utf16 + 0, utf16 + n2));
  }
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
