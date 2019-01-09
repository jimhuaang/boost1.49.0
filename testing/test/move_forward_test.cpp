#include <iostream>

#include "boost/bind.hpp"
#include "boost/move/move.hpp"
#include "boost/make_shared.hpp"
#include "boost/shared_ptr.hpp"

using boost::forward;
using boost::make_shared;
using boost::shared_ptr;

template <typename T>
struct Factory
{
  typedef shared_ptr<T> Pointer;

  Pointer Create(void) const {
    return make_shared<T>();
  }

  template <typename A0>
  Pointer Create(BOOST_FWD_REF(A0) a0) const{
    return make_shared<T>(forward<A0>(a0));
  }

  template<typename A0, typename A1>
  Pointer Create(BOOST_FWD_REF(A0) a0, BOOST_FWD_REF(A1) a1) const {
    return make_shared<T>(forward<A0>(a0), forward<A1>(a1));
  }
};


struct A {
  A(void) {
    std::cout <<"A constructor" << std::endl;
  }
};

struct B {
  B(const int &v) : m_v(v){
    std::cout << "B constructor: " << v << std::endl;
  }

  int Value(void) const {
    return m_v;
  }

private:
  const int &m_v;
};


template<typename F, typename A0>
void Call(F f, BOOST_FWD_REF(A0) a0) {
  boost::bind(f, boost::forward<A0>(a0))();
}

void Print(const int &x) {
  std::cout << "X equal to " << x << std::endl;
}

int main() {
  int value = 3;

  Factory<A> factoryA;
  Factory<B> factoryB;

  shared_ptr<A> pA = factoryA.Create();
  shared_ptr<B> pB = factoryB.Create(value);

  std::cout << pB->Value() << std::endl;
  value = 5;
  std::cout << pB->Value() << std::endl;

  Call(Print, 19);
}
