#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

class board
{
private:
    int board_size;
    int peice_count;
    string game_type;
    std::vector<char> grid;

public:
    board(std::string game_type)
    {
        if (game_type == "american_checkers")
            game_type = "american_checkers";
        if (game_type == "international_checkers")
            game_type = "international_checkers";
        initalize_board();
    }
    ~board()
    {
        grid.clear();
        grid.shrink_to_fit();
    }
    int get_board_size() { return grid.size(); }

    void clear_board()
    {
        grid.clear();
    }

    void initalize_board()
    {
        int rows_per_player = -1;
        int squares_per_row;
        if (game_type == "american_chess")
            rows_per_player = 3;
        if (game_type == "international_chess")
            rows_per_player = 4;
        for (int i = 0; i < board_size * rows_per_player; i++)
        {
            grid[i] = 'b';
        }
        for (int i = (board_size * board_size) - (rows_per_player * board_size); i < board_size * board_size; i++)
        {
            grid[i] = 'w';
        }
    }

    void print_board()
    {
        int index = 0;
        for (int row = 0; row < board_size; row++)
        {

            for (int col = 0; col < board_size; col++)
            {
                if (grid[index] == '0')
                {
                }
            }
        }
    }
};