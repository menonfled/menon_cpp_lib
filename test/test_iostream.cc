// test_iostream.cc
#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <sstream>

// ostreamへの出力
void test_output()
{
  using namespace std::literals;
  using namespace menon::iostream_ops;

  std::ostringstream ss;

  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << u8"変換テスト";
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);
  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << u"変換テスト";
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);
  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << U"変換テスト";
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);
  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << L"変換テスト";
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);

  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << "変換テスト";
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);

  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << "変換テスト"s;
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);

  ss.str("");
  ss.clear(std::ostream::goodbit);
  ss << "変換テスト"sv;
  BOOST_TEST_EQ(ss.str(), "変換テスト"s);
}

// istreamからの入力
void test_input()
{
  using namespace menon::iostream_ops;

  std::istringstream ss;
  std::string const test_s = "変換テスト";

  ss.str(test_s);
  ss.clear(std::istream::goodbit);
  std::u8string u8s;
  ss >> u8s;
  BOOST_TEST(u8s == u8"変換テスト");

  ss.str(test_s);
  ss.clear(std::istream::goodbit);
  std::u16string u16s;
  ss >> u16s;
  BOOST_TEST(u16s == u"変換テスト");

  ss.str(test_s);
  ss.clear(std::istream::goodbit);
  std::u32string u32s;
  ss >> u32s;
  BOOST_TEST(u32s == U"変換テスト");

  ss.str(test_s);
  ss.clear(std::istream::goodbit);
  std::wstring ws;
  ss >> ws;
  BOOST_TEST(ws == L"変換テスト");
}

int main()
{
  test_output();
  test_input();

  return boost::report_errors();
}
