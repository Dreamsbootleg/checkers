/**
 * @file messages.h
 * @author d_bootleg
 * @brief Chess Message Definitions
 * @date 2026-04-15
 *
 *
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "defines.h"
#include <cstring>

/**
 * @brief Message Types that are sent and received. Numbered in order of their occurence.
 */
enum MessageType
{
    // SERVER MESSAGE TYPES -- used by the server to create messages, used by the client to parse messages
    setup_match = 2,
    start_game = 3,
    place_ship = 4,
    take_shot = 6,
    shot_return = 8,
    ship_dead = 9,
    game_over = 10,
    match_over = 11,
    // CLIENT MESSAGE TYPES -- used by client to create messages, used by server to parse messages
    hello = 1,
    ship_placed = 5,
    shot_taken = 7
};

/* ─────────────────────── *
 * PARSE MESSAGE FUNCTIONS *
 * ─────────────────────── */

/**
 * @brief Validates and parses a name message.
 * @param msg message buffer.
 * @param ai_name player AI buffer.
 * @return NO_ERR on valid, BAD_HELLO_MSG on invalid.
 */
ErrorNum parse_ai_name_msg(char *msg, char *ai_name);

/**
 * @brief Validates and parses an author names message.
 * @param msg message buffer.
 * @param author_names authors buffer.
 * @return NO_ERR on valid, BAD_HELLO_MSG on invalid.
 */
ErrorNum parse_author_names_msg(char *msg, char *author_names);

/// @brief Seperates a string into a vector of words
/// @param str Address to string
/// @return Returns a vector of words
vector<string> separate_string(const string &str);

#endif
