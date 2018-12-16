#include "Semaphore.hpp"

Semaphore::Semaphore() : Semaphore(0) {}

Semaphore::Semaphore(unsigned val) {
    this->freeResources = val;

    this->cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->cond), NULL);

    this->lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->lock), NULL);

    //should we check failure cases?

}

Semaphore::~Semaphore() {
    pthread_mutex_destroy(&(this->lock));
    pthread_cond_destroy(&(this->cond));
}

void Semaphore::up() {
    //like post
    pthread

}

void Semaphore::down() {
    //like wait
    pthread_mutex_lock(&(this->lock));
    while (this->freeResources == 0) {
        pthread_cond_wait(&(this->cond), &(this->lock));
    }
    this->freeResources--;
    pthread_mutex_unlock(&(this->lock));
}




