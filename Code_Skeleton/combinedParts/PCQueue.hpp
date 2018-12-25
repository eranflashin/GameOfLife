#ifndef _QUEUEL_H
#define _QUEUEL_H

#include "Headers.hpp"
#include "Semaphore.hpp"
#include "ConsumersProducerLock.hpp"
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

    ~PCQueue()= default;


private:
    queue<T> pcQ;
    Semaphore avail_items;
    ConsumersProducerLock lock;
    pthread_mutex_t queueEditingLock;
};
// Recommendation: Use the implementation of the std::queue for this exercise

template<typename T>
PCQueue<T>::PCQueue() : pcQ(), avail_items(), lock() {

    this->queueEditingLock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->queueEditingLock), nullptr);
}


template<typename T>
T PCQueue<T>::pop() {
    avail_items.down();

    lock.consumer_lock();

    pthread_mutex_lock(&queueEditingLock);
    T item = pcQ.front();
    pcQ.pop();
    pthread_mutex_unlock(&queueEditingLock);

    lock.consumer_unlock();

    return item;
}

template<typename T>
void PCQueue<T>::push(const T &item) {
    lock.producer_lock();

    pcQ.push(item);
    avail_items.up();

    lock.producer_unlock();
}


#endif