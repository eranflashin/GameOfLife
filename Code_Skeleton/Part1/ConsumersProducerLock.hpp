#ifndef __CONSUMERSPRODUCERSLOCK_H
#define __CONSUMERSPRODUCERSLOCK_H

#include "Headers.hpp"

class ConsumersProducerLock {
    public:
        ConsumersProducerLock();
        ~ConsumersProducerLock();

        void consumer_lock();
        void consumer_unlock();
        void producer_lock();
        void producer_unlock();

    private:
        int consumers_inside;
        bool producer_inside,producer_waiting;
        pthread_cond_t consume_allowed;
        pthread_cond_t produce_allowed;
        pthread_mutex_t global_lock;
};


#endif //OSHW3_READERSWRITERSLOCK_H
