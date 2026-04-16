#include <string>
#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "source/game_logic.h"
#include "source/questions.h"
#include "source/defines.h"
#include "source/server.h"

#define SOCKET_NAME "/checkers.socket"

bool debug = false;

Connection create_socket(const char *socket_name)
{
    Connection connect;

    // create and bind the socket
    if (bind_socket(&connect, (char *)socket_name) != NO_ERR)
    {
        close_sockets(&connect);
        exit_abruptly(); // critical failure, not a complete match.
    }
    return connect;
}

int main(int argc, char *argv[])
{                             // handle signals
    signal(SIGINT, SIG_IGN);  // CTRL-C
    signal(SIGTSTP, SIG_IGN); // CTRL-Z
    cout << clrscr();

    // check if a 1 was applied as an argument (debug mode)
    if (argc == 2 && strncmp(argv[1], "1", 2) == 0)
    {
        debug = true;
        cout << "\n\t~~debug mode~~\n";
    }
    cout << gotoRowCol(2, 1) << "Welcome to the Battleships AI Contest and Tester!\n\n";

    int board_size = 10, num_games = 500;
    std::string system_dir, ai_dir, socket_name, exec1, exec2, match_type;
    system_dir = std::filesystem::current_path().string();
    socket_name = system_dir + SOCKET_NAME;

    system("clear");
    int run_type = get_run_type();
    match_type = get_match_type();
    int delay = 300000;
    srand(time(NULL));

    vector<tuple<string, string>> execs = get_all_players(system_dir);
    ask_which_player(execs, "first", exec1);
    ask_which_player(execs, "second", exec2);

    Connection connect = create_socket(socket_name.c_str());
    Match match = run_match(board_size, num_games, connect, socket_name, exec1, exec2);
    close_sockets(&connect);
}

void print_error(const char *error, const char *file_name, int line)
{
    fprintf(stderr, "\n%s Error: %s (line: %d)\n", file_name, error, line);
    return;
}