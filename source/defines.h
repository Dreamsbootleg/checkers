/**
 * @file defines.h
 * @author Kaleb Hiehle
 * @brief Checkers Common Value Definitions
 * @date 2026-04-26
 */

#include <string>
#ifndef DEFINES_H
#define DEFINES_H

#define MAX_MSG_SIZE 32
#define MAX_NAME_SIZE 32
#define LOGS_DIR "/logs/"

using namespace std;

/**
 * @brief Error Number Types for returning from functions.
 */

enum ErrorNum
{
    NO_ERR,
    BAD_SOCK_CREATE,
    BAD_SOCK_NAME,
    BAD_SOCK_BIND,
    BAD_SOCK_OPT,
    BAD_FORK,
    BAD_CONNECT,
    BAD_SEND,
    BAD_RECV,
    BAD_HELLO_MSG,
    BAD_SHIP_PLACED_MSG,
    BAD_SHOT_TAKEN_MSG,
    BAD_SHIP,
    BAD_SHOT,
};

enum PlayerNum
{
    /// @brief Whether you are PLAYER 1 or PLAYER 2.
    PLAYER_1 = 1,
    PLAYER_2 = 2,
};

enum GameResult : char
{
    WIN = 'W',
    LOSS = 'L',
    TIE = 'T',
};

enum DisplayType
{
    /// @brief Don't display the Match or Contest.
    NONE,
    /// @brief Display every. single. game.
    ALL,
    /// @brief Display the last game. Default for Match, the only way to do it for Contest.
    LAST,
    /// @brief Display each different type if available (WIN, LOSS, TIE, or an ERROR).
    EACH,
    /// @brief Display every Nth game in order.
    INCREMENT,
    /// @brief Contest Display type. Display each match as it's running the contest.
    DURING,
    /// @brief Contest Display type. Display each match after the entire contest has been processed.
    AFTER,
};

struct ContestPlayer
{
    std::string exec;
    char ai_name[MAX_NAME_SIZE];
    char author_name[MAX_NAME_SIZE];
    int lives;
    int total_wins;
    int total_losses;
    int total_ties;
    int idx;
    ErrorNum error;
};

/**
 * @brief Data to store players relevant to a specific match in a contest.
 */
struct ContestMatch
{
    ContestPlayer player1;
    ContestPlayer player2;
};

/**
 * @brief Data to store about each player for the match.
 */
struct MatchPlayer
{
    char ai_name[MAX_NAME_SIZE];
    char author_name[MAX_NAME_SIZE];
    int wins;
    int losses;
    int ties;
    ErrorNum error;
};

/**
 * @brief Data to store match information. Stores two MatchPlayer instances.
 */
struct Match
{
    MatchPlayer player1;
    MatchPlayer player2;
    time_t elapsed_time;
};

struct Move
{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};
// Puts program in debug mode if set.
extern bool debug;

/**
 * @brief Prints error messages with a specific format.
 * @param error error to print.
 * @param file_name name of the file there error is from.
 * @param line line number of the file.
 */

extern void print_error(const char *error, const char *file_name, int line);

#endif