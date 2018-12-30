#ifndef __CounterBarrier_H
#define __CounterBarrier_H

#include "utils.hpp"

class Barrier {
public:
    Barrier();

    ~Barrier();

    void down();

    void wait();

    void up();

private:
    uint value;
    pthread_mutex_t glob_lock;
    pthread_cond_t zero;
};


#endif //OSHW3_CounterBarrier_H
