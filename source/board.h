#ifndef BOARD_H
#define BOARD_H

#include "defines.h"
#include <vector>

class Board
{
private:
    int board_size;
    int peice_count;
    int grid_size;
    std::string game_type;
    std::vector<char> grid;

public:
    Board();
    Board(std::string game_type);
    Board(int board_size);
    ~Board();

    int set_board_size(int size);
    int set_peice_count(int count);
    int set_grid_size(int count);
    int set_game_type(std::string);

    int get_board_size();
    int get_peice_count();
    int get_grid_size();
    std::string get_game_type();

    void clear_board();
    void print_board();
    int resize_board();
    std::vector<char> &get_grid();
    void initalize_board();

    int RCto1D(int row, int col);

    bool validate_move(Move move);
    bool validate_move(int fromRow, int fromCol, int toRow, int toCol);
    int move(int fromRow, int fromCol, int toRow, int toCol);
    int move(Move move);
};

#endif