#include <iostream>
#include <string>

#include "referee.h"
#include "board.h"
#include "defines.h"

int run_referee(std::string game_type)
{
    int player = 0; // 0 for white 1 for black
    Board game_board(game_type);
    game_board.initalize_board();
    system("clear");
    game_board.print_board();
    std::string input_move;

    while (getline(std::cin, input_move))
    {
        if (input_move.length() != 5 || !isalpha(input_move[0]) || !isnumber(input_move[1]) || !isalpha(input_move[3]) || !isnumber(input_move[4]))
        {
            printf("To move, type a1:b2\n");
            continue;
        }
        if (isupper(input_move[0]))
            input_move[0] = input_move[0] + 32;
        if (isupper(input_move[3]))
            input_move[3] = input_move[3] + 32;
        Move move;
        move.fromRow = input_move[0] - 97;
        move.fromCol = input_move[1] - 48;
        move.toRow = input_move[3] - 97;
        move.toCol = input_move[4] - 48;
        std::cout << move.fromRow << "\n";
        std::cout << move.fromCol << "\n";
        std::cout << move.toRow << "\n";
        std::cout << move.toCol << "\n";
        game_board.move(move);
        game_board.print_board();
    }

    return -1;
}