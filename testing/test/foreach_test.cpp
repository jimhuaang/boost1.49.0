#include <cctype>
#include <string>
#include <iostream>

#include "boost/foreach.hpp"

int main(int argc, char const *argv[])
{
  std::string hello ("Hello, World!");
  BOOST_FOREACH(char &ch, hello){
    ch = std::tolower(ch);
  }
  std::cout << hello << std::endl;
  return 0;
}
