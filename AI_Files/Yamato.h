/**
 * @file Yamato.cpp
 * @author Dreamsbootleg
 * @brief Checkers AI
 * @date 4/4/2025
 */

#ifndef Yamato_H
#define Yamato_H

#include <queue>
#include <set>

#include "protected/Player.h"

// PlayerExample inherits from/extends Player

// Rename this Class with your own class!
// Make sure to change all references to
// the `PlayerExample` class in both
// this file, and your c++ file

class Yamato : public Player
{
public:
    Yamato();
    ~Yamato();
    void handle_setup_match(PlayerNum player);
    void handle_start_game();

    void handle_game_over();
    void handle_match_over();

private:
    PlayerNum player;
    int board_size;
    char game_board;
    void create_board();
    void clear_board();
    void delete_board();
};

#endif
