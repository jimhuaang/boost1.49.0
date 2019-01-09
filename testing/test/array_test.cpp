
#include <boost/array.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <string>

int main() {
  using boost::array;
  using std::string;

  array<char, 3> strs;
  strs[0] = '1';
  strs[1] = '2';
  strs[2] = '3';

  string s(strs.begin(), strs.end());
  BOOST_TEST(s == string("123"));

  return boost::report_errors();
}
