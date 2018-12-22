#include "board_utils.hpp"

/*--------------------------------------------------------------------------------
									Board Utils Implementation
--------------------------------------------------------------------------------*/


 uint board_utils::board_width(bool_mat &board) {
    return board.front().size();
}

 uint board_utils::board_height(bool_mat &board) {
    return board.size();
}

 bool board_utils::in_borders(int i, int j, bool_mat &board){
    return ((i>=0 && j>=0) && (i< board_height(board) && j< board_width(board)));
}


 int board_utils::neighbors_sum(int row, int column, bool_mat &board)
{
    int sum=0;
    for(int i = row-1; i <= row+1; i++)
    {
        for(int j = column-1; j <= column+1; j++)
        {
            if(board_utils::in_borders(i,j,board)) //If target not out of bounds
            {
                if(!(i == row && j == column)) //If target is a neighbor
                {
                    if(board[i][j]) //If neighbor is alive
                    {
                        sum++;
                    }
                }
            }
        }
    }
    return sum;
}

 vector<Job> board_utils::makeJobs(bool_mat &board, uint num_threads) {
    vector<Job> jobVec;

    uint height_board=board_height(board);
    uint rows_per_reg_job=height_board/num_threads;
    uint rows_last_job=rows_per_reg_job+(height_board%num_threads);


    for(uint start_row=0; start_row<height_board-rows_last_job; start_row+=rows_per_reg_job){
        jobVec.push_back(Job{start_row,start_row+rows_per_reg_job, false});
    }

    jobVec.push_back(Job{height_board-rows_last_job,height_board,false});

     for(int i=0; i<num_threads; i++){
         jobVec.push_back(Job{0,0,true});
     }

    return jobVec;
}
