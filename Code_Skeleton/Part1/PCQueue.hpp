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
    pthread_mutex_t lock;

};
// Recommendation: Use the implementation of the std::queue for this exercise

template<typename T>
PCQueue<T>::PCQueue() : pcQueue(), availItems() {
    this->lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->lock), nullptr);

}

template<typename T>
PCQueue<T>::~PCQueue() {
    pthread_mutex_destroy(&(this->lock));
}

template<typename T>
T PCQueue<T>::pop() {
    this->availItems.down();
    pthread_mutex_lock(&(this->lock));
    T item = this->pcQueue.front();
    this->pcQueue.pop();
    pthread_mutex_unlock(&(this->lock));
    return item;
}

template<typename T>
void PCQueue<T>::push(const T &item) {
    pthread_mutex_lock(&(this->lock));
    this->pcQueue.push(item);
    availItems.up();
    pthread_mutex_unlock(&(this->lock));
}




#endif