#ifndef __GAMETHREAD_H
#define __GAMETHREAD_H

#include "Thread.hpp"
#include "utils.hpp"
#include "board_utils.hpp"
#include "../Part1/PCQueue.hpp"

using board_utils::in_borders;
using board_utils::neighbors_sum;



class ConsumerThread : public Thread {

public:
    ConsumerThread(uint id, bool_mat &curr, bool_mat &next, vector<float> &tile_hist,PCQueue<Job> &pcQueue,
            Semaphore &barrier, pthread_mutex_t &timerLock);
    ~ConsumerThread()= default;

protected:
    bool_mat &curr,&next;
    vector<float> &tile_hist;
    PCQueue<Job> &pcQueue;
    Semaphore &barrier;
    pthread_mutex_t &timerLock;
    //static pthread_mutex_t timerLock;


    void thread_workload() override;
    void execute(Job &job);
};


#endif //OSHW3_GAMETHREAD_H
