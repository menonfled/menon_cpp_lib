#include "menon/iterator.hh"
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <string_view>
#include <vector>

int main()
{
  using namespace std::literals;

  {
    constexpr auto sv = "abcde"sv;
    constexpr menon::optional_iterator<std::string_view::iterator> t(sv.begin());
    BOOST_TEST(t);
    BOOST_TEST_NOT(!t);
    auto x = t;
    BOOST_TEST_NO_THROW(t.value());
    BOOST_TEST_NO_THROW(*t);

    menon::optional_iterator<std::string_view::iterator> u(sv.begin());
    BOOST_TEST(t == u);
    BOOST_TEST(u == t);
    BOOST_TEST(t == sv.begin());
    BOOST_TEST(sv.begin() == t);

    ++u;
    BOOST_TEST(t != u);
    BOOST_TEST(u != t);
    BOOST_TEST(t != sv.begin() + 1);
    BOOST_TEST(sv.begin() + 1 != t);

    BOOST_TEST(t < u);
    BOOST_TEST(t <= u);
    BOOST_TEST(u > t);
    BOOST_TEST(u >= t);
    BOOST_TEST(sv.begin() < u);
    BOOST_TEST(t <= sv.end());
    BOOST_TEST(sv.end() > t);
    BOOST_TEST(sv.end() >= t);
  }
  {
    constexpr menon::optional_iterator<std::string_view::iterator> u;
    BOOST_TEST(!u);
    BOOST_TEST_NOT(u);
    BOOST_TEST_THROWS(u.value(), std::bad_optional_access);
    BOOST_TEST_THROWS(*u, std::bad_optional_access);
  }
  {
    std::vector v = { 1, 2, 3, 4, 5 };
    menon::optional_iterator<decltype(v)::iterator> t(v.begin());
    BOOST_TEST(t);
    BOOST_TEST_NOT(!t);
    BOOST_TEST_NO_THROW(t.value());
    BOOST_TEST_NO_THROW(*t);
    BOOST_TEST_EQ(*t, 1);
    BOOST_TEST_NO_THROW(t[2]);
    BOOST_TEST_EQ(t[2], 3);
    BOOST_TEST_EQ(*++t, 2);
    BOOST_TEST_EQ(*t++, 2);
    BOOST_TEST_EQ(*t, 3);
    BOOST_TEST_EQ(*--t, 2);
    BOOST_TEST_EQ(*t--, 2);
    BOOST_TEST_EQ(*(t + 2), 3);
    auto u = t + 2;
    BOOST_TEST_EQ(u - t, 2);
    BOOST_TEST_EQ(t - u, -2);
  }

  return boost::report_errors();
}
