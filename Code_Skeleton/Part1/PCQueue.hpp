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
	void push(const T& item); 


private:
    queue<T> pcQueue;
    Semaphore availItems;

};
// Recommendation: Use the implementation of the std::queue for this exercise

template<typename T>
T PCQueue<T>::pop() {
    return nullptr;
}

template<typename T>
void PCQueue<T>::push(const T &item) {

}


#endif