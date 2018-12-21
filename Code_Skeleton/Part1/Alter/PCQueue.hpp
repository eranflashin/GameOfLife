#ifndef _QUEUEL_H
#define _QUEUEL_H

#include "../Headers.hpp"
#include "../Semaphore.hpp"
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
    pthread_mutex_t global_lock;
    pthread_cond_t pop_allowed;
    pthread_cond_t push_allowed;
    unsigned int producers_waiting;
    unsigned int num_of_consumers;
    unsigned int available_items;
};
// Recommendation: Use the implementation of the std::queue for this exercise

template<typename T>
PCQueue<T>::PCQueue() : pcQueue(), producers_waiting(0), available_items(0), num_of_consumers(0) {
    this->global_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
    pthread_mutex_init(&(this->global_lock), nullptr);

    this->pop_allowed = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->pop_allowed), nullptr);

    this->push_allowed = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&(this->push_allowed), nullptr);
}

template<typename T>
PCQueue<T>::~PCQueue() {
    pthread_cond_destroy(&(this->push_allowed));
    pthread_cond_destroy(&(this->pop_allowed));
    pthread_mutex_destroy(&(this->global_lock));
}

template<typename T>
T PCQueue<T>::pop() {
   pthread_mutex_lock(&global_lock);
   num_of_consumers++;
   while(producers_waiting > 0 || available_items == 0){
       pthread_cond_wait(&pop_allowed,&global_lock);
   }

   available_items--;
   T item = pcQueue.front();
   pcQueue.pop();

   num_of_consumers--;

   if(num_of_consumers == 0){
       pthread_cond_signal(&push_allowed);
   }

   pthread_mutex_unlock(&global_lock);
   return item;
}

template<typename T>
void PCQueue<T>::push(const T &item) {
    pthread_mutex_lock(&global_lock);
    producers_waiting++;

    while(num_of_consumers > 0){
        pthread_cond_wait(&push_allowed,&global_lock);
    }

    producers_waiting--;
    pcQueue.push(item);
    available_items++;

    pthread_cond_signal(&pop_allowed);

    pthread_mutex_unlock(&global_lock);
}


#endif