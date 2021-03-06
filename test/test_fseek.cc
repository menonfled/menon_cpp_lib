﻿// test_fseek.cc
#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstddef>
#include <vector>
#include <fstream>

// テストデータの作成
long long make_test_file(char const* path)
{
  std::vector<std::byte> v(256, std::byte(123));
  if (auto stream = std::fopen(path, "wb"))
  {
    std::fwrite(v.data(), 1, v.size(), stream);
    std::fclose(stream);
  }
  return static_cast<long long>(v.size());
}

int main()
{
  char const* path = "test.data";
  [[maybe_unused]] auto n = make_test_file(path);

  { // fseek/ftell関数の基本的な使い方
    auto stream = std::fopen(path, "rb");
    menon::fseek(stream, 100, SEEK_SET);
    BOOST_TEST_EQ(std::ftell(stream), 100);
    BOOST_TEST_EQ(std::ftell(stream), menon::ftell(stream));
    std::fclose(stream);
  }

  { // fseek/ftell関数とfsetpos/fgetpos関数の混在
    auto stream = std::fopen(path, "rb");
    menon::fpos_t pos;
    menon::fseek(stream, 100, SEEK_SET);
    BOOST_TEST_EQ(menon::fgetpos(stream, &pos), 0);
    BOOST_TEST_EQ(pos, 100);
    BOOST_TEST_EQ(menon::fsetpos(stream, &pos), 0);
    BOOST_TEST_EQ(std::ftell(stream), 100);
    std::fclose(stream);
  }

  { // istream版のfseek関数
    std::ifstream ifs(path);
    menon::fseek(ifs, 100, SEEK_SET);
    BOOST_TEST_EQ(ifs.tellg(), 100);
  }

  { // istream版のfseek関数とfsetpos/fgetos関数の混在
    std::ifstream ifs(path);
    menon::fpos_t pos;
    menon::fseek(ifs, 100, SEEK_SET);
    BOOST_TEST_EQ(menon::fgetpos(ifs, &pos), 0);
    BOOST_TEST_EQ(pos, 100);
    BOOST_TEST_EQ(menon::fsetpos(ifs, &pos), 0);
    BOOST_TEST_EQ(ifs.tellg(), 100);
  }

  { // iostream版のfseek関数
    std::fstream fs(path);
    menon::fseek(fs, 100, SEEK_SET);
    BOOST_TEST_EQ(fs.tellp(), 100);
    BOOST_TEST_EQ(fs.tellg(), 100);
  }

  { // ostream版のfseek関数
    std::ofstream ofs(path);
    menon::fseek(ofs, 100, SEEK_SET);
    BOOST_TEST_EQ(ofs.tellp(), 100);
  }

  { // ostream版のfseek関数とfsetpos/fgetpos関数の混在
    std::ofstream ofs(path);
    menon::fpos_t pos;
    menon::fseek(ofs, 100, SEEK_SET);
    BOOST_TEST_EQ(menon::fgetpos(ofs, &pos), 0);
    BOOST_TEST_EQ(pos, 100);
    BOOST_TEST_EQ(menon::fsetpos(ofs, &pos), 0);
    BOOST_TEST_EQ(ofs.tellp(), 100);
  }

  std::remove(path);
  return boost::report_errors();
}
