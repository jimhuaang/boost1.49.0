#include "boost/function.hpp"
#include <boost/detail/lightweight_test.hpp>

int global_int = 0;

static void WriteFive() { global_int = 5; }

struct CWriteThree {
  void operator()() const { global_int = 3; }
};

using boost::function;

int main() { 
  BOOST_TEST(global_int == 0);

  typedef function<void()> VoidFunc;
  VoidFunc f1;
  BOOST_TEST(f1.empty());

  CWriteThree three;
  f1 = three;
  BOOST_TEST(f1 != 0);
  BOOST_TEST(f1);

  f1();
  BOOST_TEST(global_int == 3);

  f1.clear();
  BOOST_TEST(f1.empty());
  BOOST_TEST(f1 == 0);

  f1 = &WriteFive;
  BOOST_TEST(f1);

  f1();
  BOOST_TEST(global_int == 5);

  f1.clear();
  BOOST_TEST(f1.empty());

  f1 = WriteFive;
  BOOST_TEST(f1);

  global_int = 0;
  f1();
  BOOST_TEST(global_int == 5);

  return boost::report_errors(); 
}
