#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>

#include "board.h"

Board::Board()
{
    game_type = "none";
    board_size = -1;
    peice_count = -1;
    grid_size = -1;
}

Board::Board(int size)
{
    board_size = size;
    grid_size = size * size;
    grid.resize(grid_size);
}

Board::Board(std::string game_type)
{
    if (game_type == "american_checkers")
    {
        this->game_type = "american_checkers";
        board_size = 8;
        peice_count = 24;
        grid_size = board_size * board_size;
    }
    else if (game_type == "international_checkers")
    {
        this->game_type = "international_checkers";
        board_size = 10;
        peice_count = 40;
        grid_size = board_size * board_size;
    }
    else
    {
        throw new std::invalid_argument("no such game type!");
    }
    grid.resize(grid_size);
}

Board::~Board()
{
    grid.clear();
    grid.shrink_to_fit();
}

int Board::set_board_size(int size)
{
    if (this->board_size < 0 || size < 0)
        return -1;
    board_size = size;
    return board_size;
}

int Board::set_peice_count(int count)
{
    if (this->peice_count < 0 || count < 0)
        return -1;
    peice_count = count;
    return peice_count;
}

int Board::set_grid_size(int count)
{
    if (this->grid_size < 0 || count < 0)
        return -1;
    grid_size = count;
    return grid_size;
}

int Board::set_game_type(std::string game_type)
{
    if (this->game_type.c_str() != NULL)
        return -1;
    this->game_type = game_type;
    return this->game_type.length();
}

int Board::get_board_size()
{
    if (board_size == -1)
        return -1;
    return board_size;
}

int Board::get_peice_count()
{
    if (peice_count == -1)
        return -1;
    return peice_count;
}

int Board::get_grid_size()
{
    if (grid_size == -1)
        return -1;
    return grid_size;
}

std::string Board::get_game_type()
{
    if (game_type.c_str() == NULL)
        return NULL;
    return game_type.c_str();
}

void Board::clear_board()
{
    grid.clear();
}

void Board::print_board()
{
    int index = 0;
    printf("  ");
    for (int i = 0; i < board_size; i++)
        printf("%c", toascii(i + 65));
    printf("\n");

    for (int row = 0; row < board_size; row++)
    {
        printf("%d ", row);
        for (int col = 0; col < board_size; col++)
        {
            printf("%c", grid[index]);
            index++;
        }
        printf("\n");
    }
    printf("\n");
}

int Board::resize_board()
{
    if (grid_size == -1)
        return -1;
    grid.resize(grid_size);
    return grid.size();
}

std::vector<char> &Board::get_grid()
{
    return grid;
}

void Board::initalize_board()
{
    resize_board();
    int rows_per_player = -1;
    if (get_game_type() == "american_checkers")
        rows_per_player = 3;
    else if (get_game_type() == "international_checkers")
        rows_per_player = 4;
    else
        throw std::invalid_argument("cannot find game type!");

    int index = 0;
    std::vector<char> &grid = get_grid();
    for (int row = 0; row < get_board_size(); row++)
    {
        for (int col = 0; col < get_board_size(); col++)
        {
            grid[index] = '.'; // empty
            if ((row + col) % 2 == 1)
            {
                if (row < rows_per_player)
                {
                    grid[index] = 'b'; // black pieces
                }
                else if (row >= get_board_size() - rows_per_player)
                {
                    grid[index] = 'w'; // white pieces
                }
            }
            index++;
        }
    }
}

int Board::move(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!validate_move(fromRow, fromCol, toRow, toCol))
        return -1;
    int from = RCto1D(fromRow, fromCol);
    int to = RCto1D(toRow, toCol);
    grid.at(to) = grid.at(from);
    grid.at(from) = '.';
    return 0;
}

int Board::move(Move move)
{
    if (!validate_move(move))
        return -1;
    int from = RCto1D(move.fromRow, move.fromCol);
    int to = RCto1D(move.toRow, move.toCol);
    std::cout << grid.at(to);
    std::cout << grid.at(from);
    grid.at(to) = grid.at(from);
    grid.at(from) = '.';
    return 0;
}

int Board::RCto1D(int row, int col)
{
    return (row * board_size) + col;
}

bool Board::validate_move(Move move)
{
    if (move.fromRow > board_size || move.fromRow < 0)
        return false;
    else if (move.fromCol > board_size || move.fromCol < 0)
        return false;
    else if (move.toRow > board_size || move.toRow < 0)
        return false;
    else if (move.toCol > board_size || move.toCol < 0)
        return false;
    return true;
}

bool Board::validate_move(int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow > board_size || fromRow < 0)
        return false;
    else if (fromCol > board_size || fromCol < 0)
        return false;
    else if (toRow > board_size || toRow < 0)
        return false;
    else if (toCol > board_size || toCol < 0)
        return false;
    return true;
}