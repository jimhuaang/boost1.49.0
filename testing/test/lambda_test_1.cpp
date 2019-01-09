#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "boost/lambda/lambda.hpp"

using std::string;

int main(int argc, char const *argv[])
{
  using namespace boost::lambda;
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  std::for_each(v.begin(), v.end(), std::cout << _1 << ' ');
  std::cout << std::endl;

  string copy = "     heello    world    ";
  char ch = ' ';
  string::iterator pos = std::find_if(copy.begin(), copy.end(), ch != _1);
  copy.erase(copy.begin(), pos);
  std::cout << copy << "end" << std::endl;

  string::reverse_iterator rpos =
      std::find_if(copy.rbegin(), copy.rend(), ch != _1);
  copy.erase(rpos.base(), copy.end());
  std::cout << copy << "end" << std::endl;

  return 0;
}
