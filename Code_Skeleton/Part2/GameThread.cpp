#include "GameThread.hpp"

/*_____________--------static-functions-declarations-------___________*/

static int neighbors_sum(int row, int column, vector<vector<bool>> &curr);
static uint curr_board_width(vector<vector<bool>> &curr);
static uint curr_board_height(vector<vector<bool>> &curr);
static bool in_borders(int i, int j, vector<vector<bool>> &curr);

/*____________________________________________________________________*/


GameThread::GameThread(uint id) :Thread(id) {
    status=Waiting;
}

void GameThread::thread_workload() {
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


static bool in_borders(int i, int j, vector<vector<bool>> &curr){
    return ((i>=0 && j>=0) && (i<curr_board_height(curr) && j<curr_board_width(curr)));
}

static uint curr_board_width(vector<vector<bool>> &curr) {
    return curr.front().size();
}

static uint curr_board_height(vector<vector<bool>> &curr) {
    return curr.size();
}

