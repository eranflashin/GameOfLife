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
    Semaphore availableItems;
    pthread_mutex_t vip_lock;
    pthread_mutex_t commoners_lock;

};
// Recommendation: Use the implementation of the std::queue for this exercise

template<typename T>
PCQueue<T>::PCQueue() : pcQueue(), availableItems() {
    vip_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&vip_lock, nullptr);

    commoners_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&commoners_lock, nullptr);
}

template<typename T>
PCQueue<T>::~PCQueue() {
    pthread_mutex_destroy(&commoners_lock);
    pthread_mutex_destroy(&vip_lock);
}

template<typename T>
T PCQueue<T>::pop() {
    availableItems.down();
    pthread_mutex_lock(&commoners_lock);

    pthread_mutex_lock(&vip_lock);

    T item = pcQueue.front();
    pcQueue.pop();

    pthread_mutex_unlock(&vip_lock);

    pthread_mutex_unlock(&commoners_lock);

    return item;
}

template<typename T>
void PCQueue<T>::push(const T &item) {
    pthread_mutex_lock(&vip_lock);

    pcQueue.push(item);
    availableItems.up();

    pthread_mutex_unlock(&vip_lock);
}


#endif