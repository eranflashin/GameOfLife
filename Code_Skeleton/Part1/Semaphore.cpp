#include "Semaphore.hpp"

Semaphore::Semaphore() : Semaphore(0) {}

Semaphore::Semaphore(unsigned val) {
    this->value = val;
    this->waiting = 0;

    this->cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->cond), nullptr);

    this->lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->lock), nullptr);

}

Semaphore::~Semaphore() {
    pthread_mutex_destroy(&(this->lock));
    pthread_cond_destroy(&(this->cond));
}

void Semaphore::up() {
    //like post
    pthread_mutex_lock(&(this->lock));
    if (this->waiting > 0) {
        this->waiting--;
        pthread_cond_signal(&(this->cond));
    } else {
        this->value++;
    }
    pthread_mutex_unlock(&(this->lock));
}

void Semaphore::down() {
    //like wait
    pthread_mutex_lock(&(this->lock));
    if (this->value == 0) {
        this->waiting++;
        pthread_cond_wait(&(this->cond), &(this->lock));
    } else {
        this->value--;
    }
    pthread_mutex_unlock(&(this->lock));
}

