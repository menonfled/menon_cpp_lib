#include "menon/ctype.hh"
#include <boost/core/lightweight_test.hpp>
#include <cctype>

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
 
  using namespace std::literals;

  BOOST_TEST_EQ(menon::strtolower("0123456789AbcDEfgH"), "0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(u8"0123456789AbcDEfgH") == u8"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(L"0123456789AbcDEfgH") == L"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(u"0123456789AbcDEfgH") == u"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(U"0123456789AbcDEfgH") == U"0123456789abcdefgh");
  BOOST_TEST_EQ(menon::strtolower("0123456789AbcDEfgH"sv), "0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(u8"0123456789AbcDEfgH"sv) == u8"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(L"0123456789AbcDEfgH"sv) == L"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(u"0123456789AbcDEfgH"sv) == u"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(U"0123456789AbcDEfgH"sv) == U"0123456789abcdefgh");
  BOOST_TEST_EQ(menon::strtolower("0123456789AbcDEfgH"s), "0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(u8"0123456789AbcDEfgH"s) == u8"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(L"0123456789AbcDEfgH"s) == L"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(u"0123456789AbcDEfgH"s) == u"0123456789abcdefgh");
  BOOST_TEST(menon::strtolower(U"0123456789AbcDEfgH"s) == U"0123456789abcdefgh");

  BOOST_TEST_EQ(menon::strtoupper("0123456789AbcDEfgH"), "0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(u8"0123456789AbcDEfgH") == u8"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(L"0123456789AbcDEfgH") == L"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(u"0123456789AbcDEfgH") == u"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(U"0123456789AbcDEfgH") == U"0123456789ABCDEFGH");
  BOOST_TEST_EQ(menon::strtoupper("0123456789AbcDEfgH"sv), "0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(u8"0123456789AbcDEfgH"sv) == u8"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(L"0123456789AbcDEfgH"sv) == L"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(u"0123456789AbcDEfgH"sv) == u"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(U"0123456789AbcDEfgH"sv) == U"0123456789ABCDEFGH");
  BOOST_TEST_EQ(menon::strtoupper("0123456789AbcDEfgH"s), "0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(u8"0123456789AbcDEfgH"s) == u8"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(L"0123456789AbcDEfgH"s) == L"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(u"0123456789AbcDEfgH"s) == u"0123456789ABCDEFGH");
  BOOST_TEST(menon::strtoupper(U"0123456789AbcDEfgH"s) == U"0123456789ABCDEFGH");

  return boost::report_errors();
}