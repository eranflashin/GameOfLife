#include "Game.hpp"

/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/

Game::Game(game_params params) : 
curr(utils::parse_lines(params.filename)), next(board_height(curr)),
pcQueue(), m_threadpool(), m_tile_hist(), m_gen_hist(){
    m_gen_num=params.n_gen;
	m_thread_num=min(params.n_thread, board_height(curr));
    interactive_on=params.interactive_on;
    print_on=params.print_on;
    jobs=makeJobs(curr,m_thread_num);
}

Game::~Game() {
	_destroy_game();
}

const vector<float> Game::gen_hist() const {
	return m_gen_hist;
}

const vector<float> Game::tile_hist() const {
	return m_tile_hist;
}

uint Game::thread_num() const {
	return m_thread_num;
}


void Game::run() {

	_init_game(); // Starts the threads and all other variables you need
	print_board("Initial Board");
	for (uint i = 0; i < m_gen_num; ++i) {
		auto gen_start = std::chrono::system_clock::now();
		_step(i); // Iterates a single generation 
		auto gen_end = std::chrono::system_clock::now();
		m_gen_hist.push_back((float)std::chrono::duration_cast<std::chrono::microseconds>(gen_end - gen_start).count());
		print_board(NULL);
	} // generation loop
	print_board("Final Board");
	_destroy_game();
}

void Game::_init_game() {
	// Create threads
	for(uint id=0; id<m_thread_num; id++){
		m_threadpool.push_back(new ConsumerThread(id,curr,next,m_tile_hist,pcQueue));
	}
	// Create game fields - V (done in constructor)
	// Start the threads
	for(auto &thread: m_threadpool){
		thread->start();
	}
	//ToDo: can we assume start return ok?

	// Testing of your implementation will presume all threads are started here
}

void Game::_step(uint curr_gen) {
	// Push jobs to queue
	for(auto &job : jobs){
		pcQueue.push(job);
	}
	// Wait for the workers to finish calculating
	for(auto &thread : m_threadpool){
		thread->join();
	}

	if(curr_gen==m_gen_num-1){
		for(auto &thread: m_threadpool){
			thread->start();
		}
	}

	// Swap pointers between current and next field
	curr.swap(next);
}

void Game::_destroy_game(){
	// Destroys board and frees all threads and resources 
	// Not implemented in the Game's destructor for testing purposes. 
	// Testing of your implementation will presume all threads are joined here
}



/*--------------------------------------------------------------------------------
								
--------------------------------------------------------------------------------*/
inline void Game::print_board(const char *header) {

	if(print_on){ 

		// Clear the screen, to create a running animation 
		if(interactive_on)
			system("clear");

		// Print small header if needed
		if (header != NULL)
			cout << "<------------" << header << "------------>" << endl;
		
		// TODO: Print the board
		cout << u8"╔" << string(u8"═") * board_width(curr) << u8"╗" << endl;
		for (uint i = 0; i < board_height(curr); ++i) {
			cout << u8"║";
			for (uint j = 0; j < board_width(curr); ++j) {
				cout << (this->curr[i][j] ? u8"█" : u8"░");
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * board_width(curr) << u8"╝" << endl;

		// Display for GEN_SLEEP_USEC micro-seconds on screen 
		if(interactive_on)
			usleep(GEN_SLEEP_USEC);
	}

}

/* Function sketch to use for printing the board. You will need to decide its placement and how exactly 
	to bring in the field's parameters. 

		cout << u8"╔" << string(u8"═") * field_width << u8"╗" << endl;
		for (uint i = 0; i < field_height ++i) {
			cout << u8"║";
			for (uint j = 0; j < field_width; ++j) {
				cout << (this.curr_board[i][j] ? u8"█" : u8"░");
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * field_width << u8"╝" << endl;
*/ 



