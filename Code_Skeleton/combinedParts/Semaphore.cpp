#include "Semaphore.hpp"

Semaphore::Semaphore() : Semaphore(0) {}

Semaphore::Semaphore(uint val) {
    this->value = val;
    this->waiting = 0;

    this->cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->cond), nullptr);

    this->zero = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->zero), nullptr);

    this->lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->lock), nullptr);

}

Semaphore::~Semaphore() {
    pthread_mutex_destroy(&(this->lock));
    pthread_cond_destroy(&(this->zero));
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
        if(this->value ==0){
            pthread_cond_signal(&(this->zero));
        }
    }
    pthread_mutex_unlock(&(this->lock));
}

void Semaphore::wait(){
    pthread_mutex_lock(&this->lock);
    while(value !=0){
        pthread_cond_wait(&(this->zero),&(this->lock));
    }
    pthread_mutex_unlock(&this->lock);

}