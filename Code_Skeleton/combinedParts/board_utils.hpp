#ifndef __BOARD_UTILS_H
#define __BOARD_UTILS_H

#include "utils.hpp"

struct Job{
    uint begin_row;
    uint end_row;
    bool poison;
};

namespace board_utils{
    uint board_width(bool_mat &board);
    uint board_height(bool_mat &board);
    bool in_borders(int i, int j, bool_mat &board);
    int neighbors_sum(int row, int column, bool_mat &board);
    vector<Job> makeJobs (bool_mat &board, uint num_threads);
    vector<Job> makePoison(uint num_threads);
}


#endif //OSHW3_BOARD_UTILS_H
