// test_isctype.cc
#include "menon/ctype.hh"
#include <boost/core/lightweight_test.hpp>
#include <cctype>
#include <cstdio>

// テストコード生成用マクロの定義
#define DEF_TEST(name)  \
    BOOST_TEST_EQ(menon::is##name(c), !!std::is##name(c2));  \
    BOOST_TEST_EQ(menon::isctype(c, menon::name), !!std::is##name(c2)); \

#define DEF_TEST2(name, cond)  \
    BOOST_TEST_EQ(menon::is##name(c), (cond)(c2));  \
    BOOST_TEST_EQ(menon::isctype(c, menon::name), (cond)(c2)); \

#define DEF_TEST3(name) \
    BOOST_TEST(menon::ctype(#name) == menon::name)

// is系関数のテストコード
template <typename Char>
void test()
{
  for (int i = -1; i <= 0x80; i++)
  {
    // std::printf("0x%02x\n", i & 0xff);
    // std::fflush(stdout);

    Char c = static_cast<Char>(i);
    int c2 = static_cast<unsigned char>(c);
    DEF_TEST(cntrl);
    DEF_TEST(digit);
    DEF_TEST(punct);
    DEF_TEST(space);
    DEF_TEST(blank);
    DEF_TEST(lower);
    DEF_TEST(upper);
    DEF_TEST(alnum);
    DEF_TEST(alpha);
    DEF_TEST(graph);
    DEF_TEST(print);
    DEF_TEST(xdigit);

    constexpr auto test_octal = [](auto c) {
      return '0' <= c && c <= '7';
    };
    DEF_TEST2(octal, test_octal);

    constexpr auto test_binary = [](auto c) {
      return '0' <= c && c <= '1';
    };
    DEF_TEST2(binary, test_binary);
  }
}

int main()
{
  test<char>();
  test<wchar_t>();
  test<char8_t>();
  test<char16_t>();
  test<char32_t>();

  // ctype関数のテストコード
  DEF_TEST3(cntrl);
  DEF_TEST3(digit);
  DEF_TEST3(punct);
  DEF_TEST3(space);
  DEF_TEST3(blank);
  DEF_TEST3(lower);
  DEF_TEST3(upper);
  DEF_TEST3(alnum);
  DEF_TEST3(alpha);
  DEF_TEST3(graph);
  DEF_TEST3(print);
  DEF_TEST3(xdigit);
  DEF_TEST3(octal);
  DEF_TEST3(binary);

  return boost::report_errors();
}
