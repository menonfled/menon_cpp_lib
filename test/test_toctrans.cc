#include "menon/ctype.hh"
#include <boost/core/lightweight_test.hpp>
#include <cctype>
#include <cstdio>

template <typename Char>
void test()
{
  for (int i = -1; i <= 0x80; i++)
  {
    // std::printf("0x%02x\n", i & 0xff);
    // std::fflush(stdout);

    Char c = static_cast<Char>(i);
    int c2 = static_cast<unsigned char>(c);
    BOOST_TEST_EQ((std::uint8_t)menon::tolower(c), (std::uint8_t)std::tolower(c2));
    BOOST_TEST_EQ((std::uint8_t)menon::toupper(c), (std::uint8_t)std::toupper(c2));
    BOOST_TEST_EQ((std::uint8_t)menon::toctrans(c, menon::tolower), (std::uint8_t)std::tolower(c2));
    BOOST_TEST_EQ((std::uint8_t)menon::toctrans(c, menon::toupper), (std::uint8_t)std::toupper(c2));
  }
}

int main()
{
  test<char>();
  test<wchar_t>();
  test<char8_t>();
  test<char16_t>();
  test<char32_t>();
  BOOST_TEST(menon::ctrans("tolower") == menon::tolower<char>);
  BOOST_TEST(menon::ctrans("toupper") == menon::toupper<char>);
  return boost::report_errors();
}