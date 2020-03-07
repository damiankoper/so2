//
// Created by maja on 02.03.2020.
//

#ifndef SO2_THREAD_HPP
#define SO2_THREAD_HPP

#include "pthread.h"

#define SLEEP_INTERVAL_MILLIS_60FPS 1000 / 60

class Thread {

private:
  pthread_t _id{};

  // Prevent copying or assignment
  Thread(const Thread &arg);

  Thread &operator=(const Thread &rhs);

protected:
  bool started = false;
  bool is_join_requested = false;
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
};

#endif // SO2_THREAD_HPP
