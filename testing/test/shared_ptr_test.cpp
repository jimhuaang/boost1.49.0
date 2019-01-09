
#include "boost/make_shared.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include <boost/detail/lightweight_test.hpp>

int cnt = 0;

struct X {
  X() { ++cnt; }

  ~X() { --cnt; }

 private:
  X(const X &);
  X &operator=(const X &);
};

int *GetObject() {
  ++cnt;
  return &cnt;
}

void ReleaseObject(int *p) {
  BOOST_TEST(p == &cnt);
  --cnt;
}

int main() {
  using boost::shared_ptr;
  using boost::weak_ptr;

  shared_ptr<X> x = boost::make_shared<X>();
  BOOST_TEST(x ? true : false);
  BOOST_TEST(x.get() != 0);

  BOOST_TEST(cnt == 1);
  {
    shared_ptr<X> x1(new X);
    BOOST_TEST(cnt == 2);
    weak_ptr<X> w1(x1);
    BOOST_TEST(x1.use_count() == 1);
    BOOST_TEST(w1.use_count() == 1);
    BOOST_TEST(cnt == 2);
  }
  BOOST_TEST(cnt == 1);

  weak_ptr<X> w(x);
  BOOST_TEST(w.use_count() == x.use_count());

  {
    shared_ptr<X> x_(x);
    BOOST_TEST(x == x_);
    BOOST_TEST(cnt == 1);
    BOOST_TEST(x.use_count() == 2);
    BOOST_TEST(w.use_count() == 2);
  }
  BOOST_TEST(x.use_count() == 1);
  BOOST_TEST(w.use_count() == 1);

  BOOST_TEST(cnt == 1);
  {
    // note that both get_object and release_object deal with int*
    shared_ptr<int> p(GetObject(), ReleaseObject);
  }
  BOOST_TEST(cnt == 1);

  return boost::report_errors();
}
