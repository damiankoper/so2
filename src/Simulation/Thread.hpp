//
// Created by maja on 02.03.2020.
//

#ifndef SO2_THREAD_HPP
#define SO2_THREAD_HPP

#include "pthread.h"

class Thread {

private:
  pthread_t _id{};

  // Prevent copying or assignment
  Thread(const Thread &arg);

  Thread &operator=(const Thread &rhs);

protected:
  bool started;
  bool isJoinRequested;
  void *arg = nullptr;

  static void *exec(void *thr);

public:
  Thread();

  virtual ~Thread();

  [[nodiscard]] unsigned int tid() const;

  void start(void *threadArg = nullptr);

  void join();

  virtual void run() = 0;

  void sleep_millis(long millis);

  static const unsigned int frames_per_second = 120;
  static const unsigned int sleep_frame = 1000 / Thread::frames_per_second;
};

#endif // SO2_THREAD_HPP
