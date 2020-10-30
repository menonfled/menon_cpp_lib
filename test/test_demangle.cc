// test_demangle.cc
#include "menon/demangle.hh"
#include <boost/core/lightweight_test.hpp>

int main()
{
#if __GNUC___ || __CLANG__
  // GCCとClangはデマングルが必要になる。
  BOOST_TEST_EQ(menon::demangle(typeid(int).name()), "int");
  BOOST_TEST_EQ(menon::demangle(typeid(char*).name()), "char*");
#endif
  BOOST_TEST_EQ(menon::type_name(typeid(int)), "int");
  return boost::report_errors();
}
