#ifndef __GAMERUN_H
#define __GAMERUN_H

#include "utils.hpp"
#include "board_utils.hpp"
#include "ConsumerThread.hpp"
#include "PCQueue.hpp"
#include "CounterBarrier.hpp"

using namespace board_utils;

/*--------------------------------------------------------------------------------
								  Auxiliary Structures
--------------------------------------------------------------------------------*/
struct game_params {
	// All here are derived from ARGV, the program's input parameters. 
	uint n_gen;
	uint n_thread;
	string filename;
	bool interactive_on; 
	bool print_on; 
};

/*--------------------------------------------------------------------------------
									Class Declaration
--------------------------------------------------------------------------------*/
class Game {
public:

	Game(game_params);
	~Game();
	void run(); // Runs the game
	const vector<float> gen_hist() const; // Returns the generation timing histogram  
	const vector<float> tile_hist() const; // Returns the tile timing histogram
	uint thread_num() const; //Returns the effective number of running threads = min(thread_num, field_height)


protected: // All members here are protected, instead of private for testing purposes

	// See Game.cpp for details on these three functions
	void _init_game(); 
	void _step(uint curr_gen);

	void _destroy_game();

	inline void print_board(const char *header);


	uint m_gen_num; 			 // The number of generations to run
	uint m_thread_num; 			 // Effective number of threads = min(thread_num, field_height)
	vector<float> m_tile_hist;     // Shared Timing history for tiles: First m_thread_num cells are the calculation durations for tiles in generation 1 and so on.
							   	 // Note: In your implementation, all m_thread_num threads must write to this structure. 
	vector<float> m_gen_hist;  	 // Timing history for generations: x=m_gen_hist[t] iff generation t was calculated in x microseconds
	vector<Thread *> m_threadpool;// A storage container for your threads. This acts as the threadpool.

	bool interactive_on; // Controls interactive mode - that means, prints the board as an animation instead of a simple dump to STDOUT
	bool print_on; // Allows the printing of the board. Turn this off when you are checking performance (Dry 3, last question)

private:
	// TODO: Add in your variables and synchronization primitives
	bool_mat curr,next;
    PCQueue<Job> pcQueue;
    vector<Job> jobs;
    Barrier barrier;
    pthread_mutex_t timerLock;
};
#endif
