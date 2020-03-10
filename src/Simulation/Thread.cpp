#include "Thread.hpp"
#include <thread>

Thread::Thread() : isJoinRequested(false), started(false) {}

Thread::~Thread() = default;

unsigned int Thread::tid() const { return 0; }

void Thread::start(void *threadArg) {
  int ret;
  this->arg = threadArg;
  /*
   * Since pthread_create is a C library function, the 3rd argument is
   * a global function that will be executed by the thread. In C++, we
   * emulate the global function using the static member function that
   * is called exec. The 4th argument is the actual argument passed to
   * the function exec. Here we use this pointer, which is an instance
   * of the Thread class.
   */
  if ((ret = pthread_create(&_id, nullptr, &Thread::exec, this)) != 0) {
    throw "Error";
  }
}

void Thread::join() {
  // Allow the thread to wait for the termination status
  this->isJoinRequested = true;
  pthread_join(_id, nullptr);
}

void *Thread::exec(void *thr) {
  // Function that is to be executed by the thread
  reinterpret_cast<Thread *>(thr)->run();
}

void Thread::sleep_millis(long millis) {
  std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}
