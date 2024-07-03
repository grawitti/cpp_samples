#include <iostream>
#include <thread>
#include <stdio.h>
#include <functional>
#include <vector>

/*
 * C++ Concurency in Action second edition Anthony Williams
 *
 * Chapter 2 samples 
 */

using namespace std;

auto vec_ref(int& i1, int& i2, int& i3)
{
  vector<reference_wrapper<int>> vref;

  vref.push_back(ref(i1));
  vref.push_back(ref(i2));
  vref.push_back(ref(i3));

  return vref;
}

void f(int i, string const& s)
{
  cout << __PRETTY_FUNCTION__ << ": " << s << "." << i << endl;
}

// Chapter 2 path 2 page 53
void c2p2_oops(int some_param)
{
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  thread t(f, 2, string(buffer));
  // thread t(f, 2, buffer); // not recomemded by A. Williams
  t.detach();
}

// Chapter 2 path 3
void c2p3()
{
  thread t1(f, 30, string("c2p3"));
  thread t2 = move(t1);
  t1 = thread(f, 31 , string("c2p3"));
  thread t3;
  t3=move(t2);
  
  cout << __PRETTY_FUNCTION__ << ": t1 id: " << t1.get_id() << ", t2 id: "
       << t2.get_id() << ", t3 id: " << t3.get_id() << endl;

  t1.join();
  t3.join();
}

// Chapter 2 path 4
void c2p4()
{
  cout << __PRETTY_FUNCTION__ << ": thread::hardware_concurrency(): "
       << thread::hardware_concurrency() << endl;
}

// Chapter 2 path 5
void c2p5()
{
  thread::id this_thread_id = this_thread::get_id();
  thread t2;
  thread::id t2_id = t2.get_id();
  if (t2_id != this_thread_id) {
    cout << __PRETTY_FUNCTION__ << ": thread t2 id: " << t2.get_id()
         << ", this_thred_id: " << this_thread::get_id() << endl;
  }
  else {
    cout << __PRETTY_FUNCTION__ << ": thread t2 id: " << t2.get_id() << endl;
  }
}

int main()
{
  c2p2_oops(2);
  // timer for wait on this thread
  constexpr int TIMER = 100000;
  for (int i = 0; i < TIMER; i++) {}

  c2p3();

  c2p4();

  c2p5();

  return 0;
}
