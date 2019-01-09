
#include "boost/thread/mutex.hpp"
#include "boost/thread/condition_variable.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/thread_time.hpp>

#include <boost/detail/lightweight_test.hpp>

using boost::mutex;


unsigned const timeout_seconds=5;

struct wait_for_flag
{
boost::mutex mutex;
boost::condition_variable cond_var;
bool flag;
unsigned woken;
    
wait_for_flag():
    flag(false),woken(0)
{}

struct check_flag
{
    bool const& flag;
        
    check_flag(bool const& flag_):
        flag(flag_)
    {}
        
    bool operator()() const
    {
        return flag;
    }
private:
    void operator=(check_flag&);
};

    
void wait_without_predicate()
{
    boost::mutex::scoped_lock lock(mutex);
    while(!flag)
    {
        cond_var.wait(lock);
    }
    ++woken;
}

void wait_with_predicate()
{
    boost::mutex::scoped_lock lock(mutex);
    cond_var.wait(lock,check_flag(flag));
    if(flag)
    {
        ++woken;
    }
}

void timed_wait_without_predicate()
{
    boost::system_time const timeout=boost::get_system_time()+boost::posix_time::seconds(timeout_seconds);
        
    boost::mutex::scoped_lock lock(mutex);
    while(!flag)
    {
        if(!cond_var.timed_wait(lock,timeout))
        {
            return;
        }
    }
    ++woken;
}

void timed_wait_with_predicate()
{
    boost::system_time const timeout=boost::get_system_time()+boost::posix_time::seconds(timeout_seconds);
    boost::mutex::scoped_lock lock(mutex);
    if(cond_var.timed_wait(lock,timeout,check_flag(flag)) && flag)
    {
        ++woken;
    }
}
void relative_timed_wait_with_predicate()
{
    boost::mutex::scoped_lock lock(mutex);
    if(cond_var.timed_wait(lock,boost::posix_time::seconds(timeout_seconds),check_flag(flag)) && flag)
    {
        ++woken;
    }
}
};


int main() {

  mutex m1;
  {
    // test lock constructor
    // typedef unique_lock<mutex> scoped_lock;
    mutex::scoped_lock lock(m1, boost::defer_lock);
    BOOST_TEST(!lock);
  }

  mutex::scoped_lock lock(m1);
  BOOST_TEST(lock);

  // typedef condition_variable_any condition;
  boost::condition_variable cond;
  cond.timed_wait(lock, boost::posix_time::milliseconds(25));
  BOOST_TEST(lock);

  lock.unlock();
  BOOST_TEST(!lock);
  lock.lock();
  BOOST_TEST(lock);

  //boost::this_thread::sleep(boost::posix_time::milliseconds(30));
  //BOOST_TEST(lock);

  return boost::report_errors();
}
