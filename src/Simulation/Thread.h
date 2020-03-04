//
// Created by maja on 02.03.2020.
//

#ifndef SO2_THREAD_H
#define SO2_THREAD_H

#include "pthread.h"

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

    unsigned int tid() const;

    void start(void *threadArg = nullptr);

    void join();

    virtual void run() = 0;
};


#endif //SO2_THREAD_H
