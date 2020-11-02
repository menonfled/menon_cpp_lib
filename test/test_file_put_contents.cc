// test_file_put_contents.cc
#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <vector>
#include <span>

std::byte test_data[256];

// テストコードが書き出したテストデータの読み込み
std::vector<std::byte> get_test_file(char const* path)
{
  auto stream = std::fopen(path, "rb");
  BOOST_TEST_NE(stream, nullptr);

  std::vector<std::byte> r;
  int c;
  while ((c = std::getc(stream)) != EOF)
    r.push_back(static_cast<std::byte>(c));
  std::fclose(stream);
  std::remove(path);
  return r;
}

// stream_put_contents関数のテストコード
void test_stream_put_contents(char const* path)
{
  auto n = sizeof(test_data);

  { // FILE*版の基本的な使い方
    auto stream = std::fopen(path, "wb");
    BOOST_TEST_NE(stream, nullptr);
    BOOST_TEST_EQ(menon::stream_put_contents(stream, test_data), n);
    std::fclose(stream);
    auto data = get_test_file(path);
    BOOST_TEST_EQ(data.size(), n);
    BOOST_TEST_EQ(std::memcmp(data.data(), test_data, n), 0);
  }
  {
    { // ostream版の基本的な使い方
      std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
      BOOST_TEST(ofs.is_open());
      BOOST_TEST_EQ(menon::stream_put_contents(ofs, std::span<std::byte>(test_data)), n);
      // ここでofsをclose
    }
    auto data = get_test_file(path);
    BOOST_TEST_EQ(data.size(), n);
    BOOST_TEST_EQ(std::memcmp(data.data(), test_data, n), 0);
  }
}

// file_put_contents関数のテストコード
void test_file_put_contents(char const* path)
{
  auto n = sizeof(test_data);

  { // 配列の書き出し
    BOOST_TEST_EQ(menon::file_put_contents(path, test_data), n);
    auto data = get_test_file(path);
    BOOST_TEST_EQ(data.size(), n);
    BOOST_TEST_EQ(std::memcmp(data.data(), test_data, n), 0);
  }
  { // vectorの書き出し
    std::vector<std::byte> v(test_data, test_data + n);
    BOOST_TEST_EQ(menon::file_put_contents(path, v), n);
    auto data = get_test_file(path);
    BOOST_TEST_EQ(data.size(), n);
    BOOST_TEST_EQ(std::memcmp(data.data(), test_data, n), 0);
  }
  { // spanを用いての追記
    menon::file_put_contents(path, test_data);
    menon::file_put_contents(path, std::span<std::byte>(test_data), menon::FILE_APPEND);
    auto data = get_test_file(path);
    BOOST_TEST_EQ(data.size(), n * 2);
    BOOST_TEST_EQ(std::memcmp(data.data(), test_data, n), 0);
    BOOST_TEST_EQ(std::memcmp(data.data() + n, test_data, n), 0);
  }
}

int main()
{
  // テストデータの作成
  for (std::size_t i = 0; i < sizeof(test_data); i++)
    test_data[i] = static_cast<std::byte>(std::rand() & 0xff);

  auto path = "test.data";
  test_stream_put_contents(path);
  test_file_put_contents(path);
  return boost::report_errors();
}
