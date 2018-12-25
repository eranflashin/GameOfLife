#include "ConsumersProducerLock.hpp"

ConsumersProducerLock::ConsumersProducerLock() : consumers_inside(0),producer_inside(false), producer_waiting(false) {
    this->global_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->global_lock), nullptr);

    this->consume_allowed = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->consume_allowed), nullptr);

    this->produce_allowed = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->produce_allowed), nullptr);
}

ConsumersProducerLock::~ConsumersProducerLock() {
    pthread_cond_destroy(&produce_allowed);
    pthread_cond_destroy(&consume_allowed);
    pthread_mutex_destroy(&global_lock);
}

void ConsumersProducerLock::consumer_lock() {
    pthread_mutex_lock(&global_lock);

    while(producer_inside || producer_waiting){
        pthread_cond_wait(&consume_allowed,&global_lock);
    }

    consumers_inside++;

    pthread_mutex_unlock(&global_lock);
}

void ConsumersProducerLock::consumer_unlock() {
   pthread_mutex_lock(&global_lock);

    consumers_inside--;

    if(consumers_inside == 0){
        pthread_cond_signal(&produce_allowed);
    }

   pthread_mutex_unlock(&global_lock);
}

void ConsumersProducerLock::producer_lock() {
    pthread_mutex_lock(&global_lock);

    producer_waiting=true;
    while(consumers_inside>0){
        pthread_cond_wait(&produce_allowed,&global_lock);
    }

    producer_waiting=false;
    producer_inside=true;

    pthread_mutex_unlock(&global_lock);
}

void ConsumersProducerLock::producer_unlock() {
    pthread_mutex_lock(&global_lock);

    producer_inside=false;

    pthread_cond_broadcast(&consume_allowed);
    pthread_cond_signal(&produce_allowed);

    pthread_mutex_unlock(&global_lock);
}
