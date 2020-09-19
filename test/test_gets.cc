#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <fstream>
#include <cwchar>

void make_test_file(char const* path)
{
  std::ofstream ofs(path);
  ofs << "これはテストです。" << std::endl;
  ofs << "デフォルトの内部エンコーディングで文字列を表しています。" << std::endl;
  ofs.close();
  std::freopen(path, "r", stdin);
}

int main()
{
  auto path = "test.data";

  make_test_file(path);
  char buf[256] {};
  wchar_t wbuf[256] {};
  std::string s;

  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256), "デフォルトの内部エンコーディングで文字列を表しています。");
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf), "デフォルトの内部エンコーディングで文字列を表しています。");
  std::rewind(stdin);
  BOOST_TEST_EQ(menon::gets(s), "これはテストです。");
  BOOST_TEST_EQ(menon::gets(s), "デフォルトの内部エンコーディングで文字列を表しています。");
  std::rewind(stdin);
  menon::gets(wbuf, 256);
  BOOST_TEST_EQ(std::wcscmp(wbuf, L"これはテストです。"), 0);
  menon::gets(wbuf, 256);
  BOOST_TEST_EQ(std::wcscmp(wbuf, L"デフォルトの内部エンコーディングで文字列を表しています。"), 0);

  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256, std::cin), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。");
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf, std::cin), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。");
  std::rewind(stdin);
  BOOST_TEST_EQ(menon::gets(s, std::cin), "これはテストです。");
  BOOST_TEST_EQ(menon::gets(s, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。");

  std::fclose(stdin);
  std::remove(path);

  return boost::report_errors();
}
