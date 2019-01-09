
#include <functional>

#include "boost/bind.hpp"
#include "boost/function.hpp"
#include <boost/detail/lightweight_test.hpp>
#include "boost/thread/once.hpp"
#include "boost/typeof/typeof.hpp"


long f_0() {
  return 123L;
}

long f_1(long a) {
  return a;
}

long f_2(long a, long b) {
  return a + b;
}

struct F{
  int operator() (int a, int b) {
    return a + b;
  }
};

struct X {
  X() : v(0) {}
  int v;
  void set(int i) { v = i; }
};

using namespace boost;

static once_flag flag = BOOST_ONCE_INIT;
struct Y {
  Y() : v(0) {}
  int v;
  void Add(int i) { call_once(flag, bind(type<void>(), &Y::DoAdd, this, i)); }

  void DoAdd(int i) {
    v += i;
  }
};

struct DataX {
  int data;
  DataX(int d = 0) : data(d) {}

  bool Positive() {
    return bind(&DataX::data, this)() > 0;
  }

  bool Negative() {
    return bind(type<bool>(), std::less<int>(), data, 0)();
  }
};

int main() {
  const int i = 1;
  BOOST_TEST(bind(f_0)(i) == 123L);
  BOOST_TEST(bind(f_1, 1L)() == 1L);
  BOOST_TEST(bind(f_1, _1)(i) == 1L);
  BOOST_TEST(bind(f_2, _1, 1L)(i) == 2L);
  BOOST_TEST(bind(f_2, 1L, 2L)() == 3L);

  BOOST_TEST(bind<int>(F(), 1, 1)() == 2);
  BOOST_TEST(bind<int>(F(), 1, _1)(3) == 4);
  BOOST_TEST(bind<int>(F(), _1, _2)(2, 3) == 5);
  BOOST_TEST(bind<int>(F(), _2, _2)(2, 3) == 6);

  F f;
  BOOST_TEST(bind<int>(f, 1, _1)(6) == 7);
  boost::function<int()> ff = bind(boost::type<int>(), F(), 1, 1);
  BOOST_TEST(ff() == 2);

  boost::function<long()> f0 = bind(f_0);
  boost::function<long(long)> f1 = bind(f_1, _1);
  BOOST_TEST(f0() == 123L);
  BOOST_TEST(f1(8) == 8);

  boost::function<long()> f11 = bind(boost::type<long>(), f_1, 5);
  BOOST_TEST(f11() == 5);

  BOOST_AUTO(f12, bind(boost::type<long>(), f_1, 10));
  BOOST_TEST(f12() == 10);

  X x;
  bind(&X::set, &x, 2)();  // invoke x.set(2);
  BOOST_TEST(x.v == 2);

  Y y;
  y.Add(5);
  BOOST_TEST(y.v == 5);

  y.Add(10);
  BOOST_TEST(y.v == 5);

  // test data member
  DataX dx(5);
  BOOST_TEST(bind(&DataX::data, &dx)() ==5 );
  BOOST_TEST(dx.Positive());
  BOOST_TEST(!dx.Negative());

  return boost::report_errors();
}
