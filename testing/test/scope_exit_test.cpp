
#include <iostream>
#include "boost/scope_exit.hpp"

struct X {
  X() {
    std::cout << "X ctor" << std::endl;
  }

  ~X() {
    std::cout << "X dtor" << std::endl;
  }
};

int main() {

  X *x = new X;
  
  // Seem there is some bug in boost
  // You always need to add two brackets
  BOOST_SCOPE_EXIT((x)) {
    delete x;
    x = NULL;
  } BOOST_SCOPE_EXIT_END
}
