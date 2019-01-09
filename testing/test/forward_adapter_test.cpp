
#include <iostream>

#include "boost/bind.hpp"
#include "boost/functional/forward_adapter.hpp"
#include "boost/move/move.hpp"

void Print(const int &x) {
  std::cout << "X equal to " << x << std::endl;
}


template<typename F, typename A0>
void Call1(F f, BOOST_FWD_REF(A0) a0) {
  boost::bind(f, boost::forward<A0>(a0))();
}

int main() {

  Call1(Print, 11);

}
