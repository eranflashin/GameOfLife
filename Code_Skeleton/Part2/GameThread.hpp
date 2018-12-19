#ifndef __GAMETHREAD_H
#define __GAMETHREAD_H

#include "Thread.hpp"

enum Status {Running,Waiting,Finished,Noticed,Poison};


class GameThread : public Thread {
public:
    GameThread(uint id);
protected:
    void thread_workload() override;
    Status status;


};


#endif //OSHW3_GAMETHREAD_H
