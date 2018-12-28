#ifndef __CONSUMERTHREAD_H
#define __CONSUMERTHREAD_H

#include "Thread.hpp"
#include "utils.hpp"
#include "board_utils.hpp"
#include "PCQueue.hpp"
#include "CounterBarrier.hpp"

using board_utils::in_borders;
using board_utils::neighbors_sum;



class ConsumerThread : public Thread {

public:
    ConsumerThread(uint id, bool_mat &curr, bool_mat &next, vector<float> &tile_hist, PCQueue<Job> &pcQueue,
                   CounterBarrier &barrier, pthread_mutex_t &timerLock);
    ~ConsumerThread()= default;

protected:
    bool_mat &curr,&next;
    vector<float> &tile_hist;
    PCQueue<Job> &pcQueue;
    CounterBarrier &barrier;
    pthread_mutex_t &timerLock;

    void thread_workload() override;
    void execute(Job &job);
};


#endif //OSHW3_GAMETHREAD_H
