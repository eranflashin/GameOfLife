#include "CounterBarrier.hpp"


CounterBarrier::CounterBarrier() {

    value = 0;

    glob_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&glob_lock, nullptr);

    zero = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&zero, nullptr);
}


CounterBarrier::~CounterBarrier() {
    pthread_cond_destroy(&zero);
    pthread_mutex_destroy(&glob_lock);
}

void CounterBarrier::down() {
    pthread_mutex_lock(&glob_lock);

    value--;
    if (value == 0) {
        pthread_cond_signal(&zero);
    }

    pthread_mutex_unlock(&glob_lock);
}

void CounterBarrier::wait() {
    pthread_mutex_lock(&glob_lock);

    while (value > 0) {
        pthread_cond_wait(&zero, &glob_lock);
    }

    pthread_mutex_unlock(&glob_lock);
}

void CounterBarrier::up() {
    pthread_mutex_lock(&glob_lock);

    value++;

    pthread_mutex_unlock(&glob_lock);
}



