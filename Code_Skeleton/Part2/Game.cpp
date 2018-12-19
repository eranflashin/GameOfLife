#include "Game.hpp"

/*_____________--------static-functions-declarations-------___________*/

static int neighbors_sum(int row, int column, vector<vector<bool>> &curr);
static uint curr_board_width(vector<vector<bool>> &curr);
static uint curr_board_height(vector<vector<bool>> &curr);
static bool in_borders(int i, int j, vector<vector<bool>> &curr);

/*____________________________________________________________________*/

/**
 *
 * neighbour_sum other ranges check ?
 * Inheriting Thread: one consumer one producer
 *
 *
 *
 * **/

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
	// Create threads
	for(uint id=0; id<m_thread_num; id++){
		m_threadpool.push_back(new GameThread(id));
	}

	pcQueue=PCQueue<Thread*>();

	this->curr_board = utils::parse_lines(filename);
	// Start the threads - IRRELEVANT
	// Testing of your implementation will presume all threads are started here
}

void Game::_step(uint curr_gen) {
	// Push jobs to queue - IRRELEVANT
	// Wait for the workers to finish calculating  -IRRELEVANT
	// For the serial implementation, the game will be implemented here
	vector<vector<bool>> next;
	vector<bool> new_row;

	int i=0;
	for(auto &line : curr_board){
	    new_row.clear();
		int j=0;
		for (auto &&curr_cell : line) {
			// Game Logic:
			if(curr_cell) // If piece is alive
			{
				if(neighbors_sum(i,j,curr_board) == 2 || neighbors_sum(i,j,curr_board)==3)
				{
					new_row.push_back(true); // If a piece has 2 or 3 neighbors, it'll stay alive
				}else{
					new_row.push_back(false); // Otherwise it'll die
				}
			}

			else // If a piece is dead
			{
				if(neighbors_sum(i,j,curr_board) == 3)
				{
					new_row.push_back(true); // If a dead piece has 3 neighbors, it revives
				}else{
					new_row.push_back(false); //Otherwise it stays dead
				}
			}

			j++;
		}

		i++;
		next.push_back(new_row);
	}

	// Swap pointers between current and next field
	this->curr_board = next;
}

void Game::_destroy_game(){
	// Destroys board and frees all threads and resources 
	// Not implemented in the Game's destructor for testing purposes. 
	// Testing of your implementation will presume all threads are joined here
}

static int neighbors_sum(int row, int column, vector<vector<bool>> &curr)
{
	int sum=0;
	for(int i = row-1; i <= row+1; i++)
	{
		for(int j = column-1; j <= column+1; j++)
		{
			if(in_borders(i,j,curr)) //If target not out of bounds
			{
				if(!(i == row && j == column)) //If target is a neighbor
				{
					if(curr[i][j]) //If neighbor is alive
					{
						sum++;
					}
				}
			}
		}
	}
	return sum;
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


static bool in_borders(int i, int j, vector<vector<bool>> &curr){
	return ((i>=0 && j>=0) && (i<curr_board_height(curr) && j<curr_board_width(curr)));
}

static uint curr_board_width(vector<vector<bool>> &curr) {
	return curr.front().size();
}

static uint curr_board_height(vector<vector<bool>> &curr) {
	return curr.size();
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



