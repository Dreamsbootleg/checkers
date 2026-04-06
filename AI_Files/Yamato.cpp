/**
 * @file Yamato.cpp
 * @author Dreamsbootleg
 * @brief Checkers AI
 * @date 4/3/2026
 */

#include <fstream>
#include <iomanip>
#include <random>

#include "Yamato.h"

// Write your AI's name here. Please don't make it more than 64 bytes.
#define AI_NAME "Yamato"

// Write your name(s) here. Please don't make it more than 64 bytes.
#define AUTHOR_NAMES "Dreamsbootleg"

/*================================================================================
 * Starts up the entire match. Do NOT change anything here unless you really
 *understand what you are doing.
 *================================================================================*/
int main(int argc, char *argv[])
{
    // player must have the socket path as an argument.
    if (argc != 2)
    {
        printf("%s Error: Requires socket name! (line: %d)\n", AI_NAME,
               __LINE__);
        return -1;
    }
    char *socket_path = argv[1];

    // set random seed
    srand(getpid());

    Yamato my_player = Yamato();
    return my_player.play_match(socket_path, AI_NAME, AUTHOR_NAMES);
}