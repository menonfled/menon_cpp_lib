#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <sstream>

int main()
{
  std::ostringstream ss;
  using namespace std::literals;
  using namespace menon::iostream_ops;

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

  return boost::report_errors();
}
