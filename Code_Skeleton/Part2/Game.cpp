#include "Game.hpp"

/*--------------------------------------------------------------------------------

--------------------------------------------------------------------------------*/

Game::Game(game_params params) {
    this->m_gen_num=params.n_gen;
    this->m_thread_num=params.n_thread;
    this->filename=params.filename;
    this->interactive_on=params.interactive_on;
    this->print_on=params.print_on;
}

Game::~Game() {
	// later on
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

void Game::_init_game() { //SERIAL IMPLEMENTATION
	this->curr_board = utils::parse_lines(filename);

	// Create threads
	for(uint id=0; id<m_thread_num; id++){
		m_threadpool.push_back(new GameThread(id));
	}

	pcQueue=PCQueue<Thread*>();

	for(auto &thrd: m_threadpool){
		thrd->start();
	}

	// Testing of your implementation will presume all threads are started here
}

void Game::_step(uint curr_gen) {
	// Push jobs to queue - IRRELEVANT
	for(auto& thrd: m_threadpool){



		pcQueue.push(thrd);
	}

	while(size(PCQueue)!= 0)
	{
		if()
	}

	// Wait for the workers to finish calculating  -IRRELEVANT
	// For the serial implementation, the game will be implemented here

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
		cout << u8"╔" << string(u8"═") * curr_board_width(curr_board) << u8"╗" << endl;
		for (uint i = 0; i < curr_board_height(curr_board); ++i) {
			cout << u8"║";
			for (uint j = 0; j < curr_board_width(curr_board); ++j) {
				cout << (this->curr_board[i][j] ? u8"█" : u8"░");
			}
			cout << u8"║" << endl;
		}
		cout << u8"╚" << string(u8"═") * curr_board_width(curr_board) << u8"╝" << endl;

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



