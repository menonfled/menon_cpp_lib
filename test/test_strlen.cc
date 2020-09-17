#include "menon/string.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
  std::string s = "abcdefghi";
  std::size_t n = s.size();

  BOOST_TEST_EQ(menon::strlen(s), n);
  BOOST_TEST_EQ(menon::strlen(s.c_str()), n);
  BOOST_TEST_EQ(menon::strlen(s.c_str(), s.size()), n);
  BOOST_TEST_EQ(menon::strlen(std::string_view(s)), n);

  return boost::report_errors();
}
