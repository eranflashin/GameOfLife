#ifndef __GAMETHREAD_H
#define __GAMETHREAD_H

#include "Thread.hpp"

class GameThread : public Thread {
protected:
    void thread_workload() override;
};


#endif //OSHW3_GAMETHREAD_H
