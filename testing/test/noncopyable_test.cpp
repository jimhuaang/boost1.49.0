#include <iostream>

#include "boost/noncopyable.hpp"

namespace {
  class DontTreadOnMe : private boost::noncopyable {
  public:
    DontTreadOnMe() {
      std::cout << "defanged!" << std::endl;
    }
  };
}

int main() {
  DontTreadOnMe obj1;
  //DontTreadOnMe obj2(obj1);

  DontTreadOnMe obj3;
  //obj1 = obj3;
  return 0;
}
