// test_gets.cc
#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <fstream>
#include <cwchar>

// テストデータの作成
void make_test_file(char const* path)
{
  std::ofstream ofs(path);
  ofs << "これはテストです。" << std::endl;
  ofs << "デフォルトの内部エンコーディングで文字列を表しています。" << std::endl;
}

// gets関数のテストコード
void test_gets(char const* path)
{
  char buf[256] {};
  wchar_t wbuf[256] {};
  std::string s;

  // 標準入力をテストデータにバインド
  std::freopen(path, "r", stdin);

  // サイズを指定する場合
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256), "デフォルトの内部エンコーディングで文字列を表しています。");

  // 配列の要素数を使用する場合
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf), "デフォルトの内部エンコーディングで文字列を表しています。");

  // stringを使用する場合
  std::rewind(stdin);
  BOOST_TEST_EQ(menon::gets(s), "これはテストです。");
  BOOST_TEST_EQ(menon::gets(s), "デフォルトの内部エンコーディングで文字列を表しています。");

  // ワイド文字版
  std::rewind(stdin);
  menon::gets(wbuf, 256);
  BOOST_TEST_EQ(std::wcscmp(wbuf, L"これはテストです。"), 0);
  menon::gets(wbuf, 256);
  BOOST_TEST_EQ(std::wcscmp(wbuf, L"デフォルトの内部エンコーディングで文字列を表しています。"), 0);

  // istream版でサイズを指定する場合
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256, std::cin), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf, 256, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。");

  // istream版で配列の要素数を使用する場合
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf, std::cin), "これはテストです。");
  BOOST_TEST_CSTR_EQ(menon::gets(buf, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。");

  // istream版でstringを使用する場合
  std::rewind(stdin);
  BOOST_TEST_EQ(menon::gets(s, std::cin), "これはテストです。");
  BOOST_TEST_EQ(menon::gets(s, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。");

  // EOFの場合
  std::fseek(stdin, 0L, SEEK_END);
  BOOST_TEST_CSTR_EQ(menon::gets(buf), "");

  // クローズ済みの場合
  std::fclose(stdin);
  BOOST_TEST_CSTR_EQ(menon::gets(buf), "");
}

// fgets関数のテストコード
void test_fgets(char const* path)
{
  char buf[256] {};
  wchar_t wbuf[256] {};
  std::string s;

  // 標準入力をテストデータにバインド
  std::freopen(path, "r", stdin);

  // 配列を使う場合  
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::fgets(buf, 256, stdin), "これはテストです。\n");
  BOOST_TEST_CSTR_EQ(menon::fgets(buf, 256, stdin), "デフォルトの内部エンコーディングで文字列を表しています。\n");

  // stringを使う場合
  std::rewind(stdin);
  BOOST_TEST_EQ(menon::fgets(s, 256, stdin), "これはテストです。\n");
  BOOST_TEST_EQ(menon::fgets(s, 256, stdin), "デフォルトの内部エンコーディングで文字列を表しています。\n");

  // ワイド文字列版
  std::rewind(stdin);
  menon::fgets(wbuf, 256, stdin);
  BOOST_TEST_EQ(std::wcscmp(wbuf, L"これはテストです。\n"), 0);
  menon::fgets(wbuf, 256, stdin);
  BOOST_TEST_EQ(std::wcscmp(wbuf, L"デフォルトの内部エンコーディングで文字列を表しています。\n"), 0);

  // istream版
  std::rewind(stdin);
  BOOST_TEST_CSTR_EQ(menon::fgets(buf, 256, std::cin), "これはテストです。\n");
  BOOST_TEST_CSTR_EQ(menon::fgets(buf, 256, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。\n");

  // istream版でstringを使う場合
  std::rewind(stdin);
  BOOST_TEST_EQ(menon::fgets(s, 256, std::cin), "これはテストです。\n");
  BOOST_TEST_EQ(menon::fgets(s, 256, std::cin), "デフォルトの内部エンコーディングで文字列を表しています。\n");

  // EOFの場合
  std::fseek(stdin, 0L, SEEK_END);
  BOOST_TEST_CSTR_EQ(menon::fgets(buf, 256, stdin), "");

  // クローズ済みの場合
  std::fclose(stdin);
  BOOST_TEST_CSTR_EQ(menon::fgets(buf, 256, stdin), "");
}

int main()
{
  auto path = "test.data";

  make_test_file(path);
  test_gets(path);

  make_test_file(path);
  test_fgets(path);

  std::remove(path);

  return boost::report_errors();
}
