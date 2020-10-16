#include "menon/io.hh"
#include <boost/core/lightweight_test.hpp>
#include <cstddef>
#include <vector>
#include <fcntl.h>
#if __has_include(<unistd.h>)
# include <unistd.h>
#elif __has_include(<io.h>)
# include <io.h>
#endif

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
  auto n = make_test_file(path);

  int fd = open(path, O_RDONLY | O_BINARY);
  BOOST_TEST_GE(fd, 0);
  BOOST_TEST_EQ(menon::filelength(fd), n);
  close(fd);

  auto stream = fopen(path, "r");
  BOOST_TEST_NE(stream, nullptr);
  BOOST_TEST_EQ(menon::filelength(stream), n);
  fclose(stream);

  std::filesystem::path t(path);
  BOOST_TEST_EQ(menon::filelength(t), n);
  BOOST_TEST_EQ(menon::filesize(t), n);
  BOOST_TEST_EQ(menon::filesize(path), n);

  std::remove(path);
  return boost::report_errors();
}
