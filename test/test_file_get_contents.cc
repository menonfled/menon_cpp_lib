// test_file_get_contents.cc
#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <fstream>
#include <sstream>
#include <cwchar>
#include <cstdlib>

std::byte test_data[256];

// テストデータの作成
void make_test_file(char const* path)
{
  for (std::size_t i = 0; i < sizeof(test_data); i++)
    test_data[i] = static_cast<std::byte>(std::rand() & 0xff);
  auto stream = std::fopen(path, "wb");
  BOOST_TEST_NE(stream, nullptr);
  std::fwrite(test_data, 1, sizeof(test_data), stream);
  std::fclose(stream);
}

// stream_get_contents関数のテストコード
void test_stream_get_contents(char const* path)
{
  auto stream = std::fopen(path, "rb");
  BOOST_TEST_NE(stream, nullptr);
  { // 基本的な使い方
    std::rewind(stream);
    auto r = menon::stream_get_contents(stream);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data), std::end(test_data)));
  }
  { // offsetを指定
    std::rewind(stream);
    auto r = menon::stream_get_contents(stream, -1, 10);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 10, std::end(test_data)));
  }
  { // maxlengthとoffsetを設定
    std::rewind(stream);
    auto r = menon::stream_get_contents(stream, 100, 7);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 7, std::begin(test_data) + 7 + 100));
  }
  { // シーク位置からmaxlengthを設定して読み込み
    std::fseek(stream, 20, SEEK_SET);
    auto r = menon::stream_get_contents(stream, 100);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 20, std::begin(test_data) + 20 + 100));
  }
  { // シーク位置からの読み込み
    std::fseek(stream, 20, SEEK_SET);
    auto r = menon::stream_get_contents(stream);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 20, std::end(test_data)));
  }
  std::fclose(stream);

  { // istreamからの基本的な読み込み
    std::ifstream ifs(path, std::ios_base::in | std::ios_base::binary);
    auto r = menon::stream_get_contents(ifs);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data), std::end(test_data)));
  }
  { // istreamからのoffsetを指定して読み込み
    std::ifstream ifs(path, std::ios_base::in | std::ios_base::binary);
    auto r = menon::stream_get_contents(ifs, -1, 10);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 10, std::end(test_data)));
  }
  { // istreamからのmaxlengthとoffsetを指定して読み込み
    std::ifstream ifs(path, std::ios_base::in | std::ios_base::binary);
    auto r = menon::stream_get_contents(ifs, 100, 7);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 7, std::begin(test_data) + 7 + 100));
  }
  { // istreamからのシーク位置からのmaxlengthを指定して読み込み
    std::ifstream ifs(path, std::ios_base::in | std::ios_base::binary);
    ifs.seekg(20);
    auto r = menon::stream_get_contents(stream, 100);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 20, std::begin(test_data) + 20 + 100));
  }
  { // istreamからのシーク位置からの読み込み
    std::ifstream ifs(path, std::ios_base::in | std::ios_base::binary);
    ifs.seekg(20);
    auto r = menon::stream_get_contents(ifs);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 20, std::end(test_data)));
  }
}

// file_get_contents関数のテストコード
void test_file_get_contents(char const* path)
{
  { // 基本的な使い方
    auto r = menon::file_get_contents(path);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data), std::end(test_data)));
  }
  { // offsetを指定して読み込み
    auto r = menon::file_get_contents(path, -1, 10);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 10, std::end(test_data)));
  }
  { // maxlengthとoffsetを指定して読み込み
    auto r = menon::file_get_contents(path, 100, 7);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 7, std::begin(test_data) + 7 + 100));
  }
  { // 不正なパスを指定した場合の異常系処理
    BOOST_TEST_THROWS(menon::file_get_contents(":*"), std::invalid_argument); 
  }
}

int main()
{
  auto path = "test.data";

  make_test_file(path);
  test_stream_get_contents(path);
  test_file_get_contents(path);
  std::remove(path);

  return boost::report_errors();
}
