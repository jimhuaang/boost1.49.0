#include <iostream>

#include "boost/move/move.hpp"
#include "boost/make_shared.hpp"
#include "boost/shared_ptr.hpp"

#include "boost/preprocessor.hpp"

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

  /////////////////////////////////////////////////////////////////////
  #define NUM_PARAMETERS 3
  #define PARAMETERS(Z, N, D) BOOST_PP_COMMA_IF(N) \
    BOOST_FWD_REF(BOOST_PP_CAT(A, N)) BOOST_PP_CAT(a, N)
  #define FORWARD(Z, N, D) BOOST_PP_COMMA_IF(N) \
    boost::forward<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))

  #define EXPAND(N)                                              \
  template <BOOST_PP_ENUM_PARAMS(N, typename A)>                 \
  Pointer Create(BOOST_PP_REPEAT(N, PARAMETERS, ~)) const {      \
    return boost::make_shared<T>(BOOST_PP_REPEAT(N, FORWARD, ~));\
  }                                                              \

  #define BOOST_PP_LOCAL_MACRO(N) EXPAND(N)
  #define BOOST_PP_LOCAL_LIMITS   (1, NUM_PARAMETERS)
  #include BOOST_PP_LOCAL_ITERATE()

  #undef BOOST_PP_LOCAL_MACRO
  #undef BOOST_PP_LOCAL_LIMITS
  #undef EXPAND
  #undef FORWARD
  #undef PARAMETERS
  #undef NUM_PARAMETERS


  //template <typename A0>
  //Pointer Create(BOOST_FWD_REF(A0) a0) const{
  //  return make_shared<T>(forward<A0>(a0));
  //}
//
  //template<typename A0, typename A1>
  //Pointer Create(BOOST_FWD_REF(A0) a0, BOOST_FWD_REF(A1) a1) const {
  //  return make_shared<T>(forward<A0>(a0), forward<A1>(a1));
  //}
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

int main() {
  int value = 3;

  Factory<A> factoryA;
  Factory<B> factoryB;

  shared_ptr<A> pA = factoryA.Create();
  shared_ptr<B> pB = factoryB.Create(value);

  std::cout << pB->Value() << std::endl;
  value = 5;
  std::cout << pB->Value() << std::endl;
}
