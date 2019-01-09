#include <stdint.h>
#include <string>

#include "boost/exception/to_string.hpp"
#include <boost/detail/lightweight_test.hpp>

int main() {
  using boost::to_string;
  BOOST_TEST( "42" == to_string(42));
  
  uint16_t n0 = 16;
  BOOST_TEST("16" == to_string(n0));

  int16_t n1 = -16;
  BOOST_TEST("-16" == to_string(n1));

  uint32_t n2 = 32;
  BOOST_TEST("32" == to_string(n2));

  int32_t n3 = -32;
  BOOST_TEST("-32" == to_string(n3));

  uint32_t n4 = 64;
  BOOST_TEST("64" == to_string(n4));

  int32_t n5 = -64;
  BOOST_TEST("-64" == to_string(n5));

  return boost::report_errors();
}
