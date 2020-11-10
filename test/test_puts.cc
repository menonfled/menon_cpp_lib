// test_puts.cc
#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <cwchar>
#include <fstream>

// テストデータの読み込み
std::string read_test_file(char const* path, bool keep_nl)
{
  char buf[1024];
  if (keep_nl)
  {
    if (auto stream = std::fopen(path, "r"))
    {
      std::fgets(buf, sizeof(buf), stream);
      std::fclose(stream);
    }
  }
  else
  {
    std::ifstream ifs(path);
    ifs.getline(buf, sizeof(buf));
  }
  std::remove(path);
  return buf;
}

// puts関数のテストコード
void test_puts()
{
  using namespace std::literals;
  char const* path = "test.data";
  auto test_s = "これはテストです。";
  auto test_str = "これはテストです。"s;
  auto test_wcs = L"これはテストです。";
  auto test_wstr = L"これはテストです。"s;

  { // 文字配列の書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::puts(test_s, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, false), test_s);
  }
  { // stringの書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::puts(test_str, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, false), test_s);
  }
  { // wchar_t配列の書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::puts(test_wcs, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, false), test_s);
  }
  { // wstringの書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::puts(test_wstr, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, false), test_s);
  }
}

// fputs関数のテストコード
void test_fputs()
{
  using namespace std::literals;
  char const* path = "test.data";
  auto test_s = "これはテストです。";
  auto test_str = "これはテストです。"s;
  auto test_wcs = L"これはテストです。";
  auto test_wstr = L"これはテストです。"s;

  { // 文字配列の書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::fputs(test_s, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, true), test_s);
  }
  { // stringの書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::fputs(test_str, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, true), test_s);
  }
  { // wchar_t配列の書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::fputs(test_wcs, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, true), test_s);
  }
  { // wstringの書き込み
    auto stream = std::fopen(path, "w");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::fputs(test_wstr, stream), 0);
    std::fclose(stream);
    BOOST_TEST_EQ(read_test_file(path, true), test_s);
  }
}

int main()
{
  test_puts();
  test_fputs();
  return boost::report_errors();
}
