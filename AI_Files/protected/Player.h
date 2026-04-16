/**
 * @file Player.h
 * @author dreamsbootleg
 * @brief The Base Class for Player AIs.
 * @date 2026-4-04
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cerrno>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <map>
#include <vector>

#include "../../source/defines.h"

class Player
{
private:
    /// @brief The defined socket descriptor for the Player.
    int socket_desc;

    /// @brief Message buffer for sending and receiving messages.
    char msg[MAX_MSG_SIZE];

public:
    /// @brief Base Player constructor. Clears the message buffer.
    Player()
    {
        memset(this->msg, 0, MAX_MSG_SIZE);
    };

    /// @brief Base Player destructor. Closes the socket.
    ~Player()
    {
        close(this->socket_desc);
    };

    void handle_setup_match();
    void handle_start_match();
    void handle_start_round();
    /// @brief Handles all message logic for the Player and inherited class meembers.
    /// @param socket_path Path to the socket.
    /// @param ai_name Name of the inherited AI.
    /// @param author_names Names of the authors of the inherited AI.
    /// @return 0 on success, -1 on error.
    int play_match(char *socket_path, const char *ai_name, const char *author_names);

    /// @brief Stores these values for the Player class
    /// and handles logic for the start of a match.
    /// This funciton is called once.
    /// @param player player number for that match.

protected:
    /// @brief Connects to the server socket created by the server.
    /// @param socket_path Path to the socket.
    /// @return 0 on success, -1 on error.
    int connect_to_socket(char *socket_path);

    /// @brief Sends a message on the message buffer.
    /// @return 0 on success, -1 on error.
    int send_msg();

    /// @brief Recieves a message from the message buffer.
    /// @return 0 on success, -1 on error.
    int recv_msg();

    /// @brief Stores setoptions
    map<string, string> setoptions;

    /// @brief Seperates a string into a vector of words
    /// @param str Address to string
    /// @return Returns a vector of words
    std::vector<std::string> seperate_string(const std::string &str);
};

#endif