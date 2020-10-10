#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstddef>
#include <vector>

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

  auto stream = std::fopen(path, "rb");
  menon::fseek(stream, 100, SEEK_SET);
  BOOST_TEST_EQ(std::ftell(stream), 100);
  std::fclose(stream);

  std::remove(path);
  return boost::report_errors();
}
