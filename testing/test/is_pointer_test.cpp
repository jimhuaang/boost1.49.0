
#include <stdio.h>

#include <iostream>
#include <vector>

#include "boost/type_traits/is_pointer.hpp"


template <typename P>
std::string PointerAddress(P p) {
  if (boost::is_pointer<P>::value) {
    int sz = snprintf(NULL, 0, "%p", p);
    std::vector<char> buf(sz + 1);
    snprintf(&buf[0], sz + 1, "%p", p);
    std::string ss(buf.begin(), buf.end());
    return ss;
  }
  return std::string();
}


int main(int argc, char const *argv[])
{
  const char *buffer = "This is for pointer test";

  std::cout <<"pointer addrress: " << PointerAddress(buffer) << std::endl;

  printf("Address of x is  %p\n", (void *)buffer);  
  
  return 0;
}
