
#include "boost/mem_fn.hpp"
#include "boost/bind.hpp"
#include "boost/function.hpp"

#include "boost/detail/lightweight_test.hpp"

struct X {
  int m;

  bool Positive() { return boost::mem_fn(&X::m)(this) > 0; }

  void SetValue(int i) { m = i; }
};

int main() {
  X x = {0};

  boost::mem_fn (&X::m)(x) = 401;
  BOOST_TEST(x.m == 401);
  BOOST_TEST(boost::mem_fn(&X::m)(x) == 401);

  boost::mem_fn (&X::m)(&x) = 502;
  BOOST_TEST(x.m == 502);
  BOOST_TEST(boost::mem_fn(&X::m)(&x) == 502);

  BOOST_TEST(x.Positive());

  boost::function<void(int)> f =
      boost::bind(boost::type<void>(), boost::mem_fn(&X::SetValue), &x, _1);
  f(10);
  BOOST_TEST(x.m == 10);

  return boost::report_errors();
}
