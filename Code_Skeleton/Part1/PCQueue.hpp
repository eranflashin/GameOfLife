#ifndef _QUEUEL_H
#define _QUEUEL_H

#include "Headers.hpp"
#include "Semaphore.hpp"
// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:
	// Blocks while queue is empty. When queue holds items, allows for a single
	// thread to enter and remove an item from the front of the queue and return it. 
	// Assumes multiple consumers.
    T pop();

	// Allows for producer to enter with *minimal delay* and push items to back of the queue.
	// Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.  
	// Assumes single producer 
    void push(const T &item);

    PCQueue();

    ~PCQueue();


private:
    queue<T> pcQueue;
    Semaphore availItems;
    pthread_mutex_t genLock;
    pthread_mutex_t producerLock;
    pthread_cond_t cond;
    unsigned int producersWaiting;

};
// Recommendation: Use the implementation of the std::queue for this exercise

template<typename T>
PCQueue<T>::PCQueue() : pcQueue(), availItems(), producersWaiting(0) {
    this->genLock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->genLock), nullptr);

    this->genLock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->producerLock), nullptr);

    this->cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->cond), nullptr);
}

template<typename T>
PCQueue<T>::~PCQueue() {
    pthread_cond_destroy(&(this->cond));
    pthread_mutex_destroy(&(this->producerLock));
    pthread_mutex_destroy(&(this->genLock));
}

template<typename T>
T PCQueue<T>::pop() {
    this->availItems.down();

    pthread_mutex_lock(&(this->genLock));

    while (this->producersWaiting > 0) {
        pthread_cond_wait(&(this->cond), &(this->genLock));
    }

    T item = this->pcQueue.front();
    this->pcQueue.pop();
    pthread_mutex_unlock(&(this->genLock));
    return item;
}

template<typename T>
void PCQueue<T>::push(const T &item) {
    pthread_mutex_lock(&(this->producerLock));
    this->producersWaiting++;
    pthread_mutex_unlock(&(this->producerLock));

    pthread_mutex_lock(&(this->genLock));
    this->pcQueue.push(item);
    this->producersWaiting--;
    pthread_cond_signal(&cond);
    availItems.up();
    pthread_mutex_unlock(&(this->genLock));
}

//TODO: try to change the producerWaiting+producerLock to semaphore. i.e use two semaphores


#endif