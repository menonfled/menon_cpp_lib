#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <fstream>
#include <sstream>
#include <cwchar>
#include <cstdlib>

std::byte test_data[256];

void make_test_file(char const* path)
{
  for (std::size_t i = 0; i < sizeof(test_data); i++)
    test_data[i] = static_cast<std::byte>(std::rand() & 0xff);
  auto stream = std::fopen(path, "wb");
  BOOST_TEST_NE(stream, nullptr);
  std::fwrite(test_data, 1, sizeof(test_data), stream);
  std::fclose(stream);
}

void test_stream_get_contents(char const* path)
{
  auto stream = std::fopen(path, "rb");
  BOOST_TEST_NE(stream, nullptr);
  {
    std::rewind(stream);
    auto r = menon::stream_get_contents(stream);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data), std::end(test_data)));
  }
  {
    std::rewind(stream);
    auto r = menon::stream_get_contents(stream, -1, 10);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 10, std::end(test_data)));
  }
  {
    std::rewind(stream);
    auto r = menon::stream_get_contents(stream, 100, 7);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 7, std::begin(test_data) + 7 + 100));
  }
  {
    std::fseek(stream, 20, SEEK_SET);
    auto r = menon::stream_get_contents(stream, 100);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 20, std::begin(test_data) + 20 + 100));
  }
  {
    std::fseek(stream, 20, SEEK_SET);
    auto r = menon::stream_get_contents(stream);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 20, std::end(test_data)));
  }
  std::fclose(stream);
}

void test_file_get_contents(char const* path)
{
  {
    auto r = menon::file_get_contents(path);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data), std::end(test_data)));
  }
  {
    auto r = menon::file_get_contents(path, -1, 10);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 10, std::end(test_data)));
  }
  {
    auto r = menon::file_get_contents(path, 100, 7);
    BOOST_TEST(std::equal(r.cbegin(), r.cend(), std::begin(test_data) + 7, std::begin(test_data) + 7 + 100));
  }
  {
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
