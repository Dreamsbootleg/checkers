#include <iostream>
#include <string>
#include <cctype>

#include "game_logic.h"
#include "board.h"
#include "defines.h"

/*int run_match(std::string game_type)
{
    int player = 0; // 0 for white 1 for black
    Board game_board(game_type);
    game_board.initalize_board();
    system("clear");
    game_board.print_board();
    std::string input_move;

    while (getline(std::cin, input_move))
    {
        if (input_move.length() != 5 || !std::isalpha(input_move[0]) || !std::isdigit(input_move[1]) || !isalpha(input_move[3]) || !isdigit(input_move[4]))
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
}*/
Match run_match(int board_size, int num_games, Connection connect, string socket_name, string exec1, string exec2)
{
    ErrorNum p1_status, p2_status;
    int status;
    Match match;
    memset(&match, 0, sizeof(Match));
    match.elapsed_time = 0;

    match.player1.error = NO_ERR;
    match.player2.error = NO_ERR;

    char msg1[MAX_MSG_SIZE];
    char msg2[MAX_MSG_SIZE];
    memset(msg1, 0, MAX_MSG_SIZE);
    memset(msg2, 0, MAX_MSG_SIZE);

    time_t start = time(NULL), end;

    /*      PLAYER STUFF        */
    char *arg1[] = {(char *)exec1.c_str(), (char *)socket_name.c_str(), NULL};
    char *arg2[] = {(char *)exec2.c_str(), (char *)socket_name.c_str(), NULL};

    // start and connect with player1
    p1_status = run_player(arg1[0], arg1, &connect.pid1);
    if (p1_status != NO_ERR)
    {
        if (connect.pid1 != -1)
            kill_player(connect.pid1);
        match.player1.losses++;
        match.player2.wins++;
        match.player1.error = p1_status;
        return match;
    }
    p1_status = accept_connection(connect.server_desc, &connect.player1_desc);

    // start and connect with player2
    p2_status = run_player(arg2[0], arg2, &connect.pid2);
    if (p2_status != NO_ERR)
    {
        kill_player(connect.pid1);
        close(connect.player1_desc);
        if (connect.pid2 != -1)
            kill_player(connect.pid2);

        match.player1.wins++;
        match.player2.losses++;
        match.player2.error = p2_status;
        return match;
    }
    p2_status = accept_connection(connect.server_desc, &connect.player2_desc);

    // check connection status of both players
    status = check_return(&match, p1_status, p2_status);
    if (status)
    { // players didn't connect, blame it on them (even if maybe it's your fault).
        kill_player(connect.pid1);
        kill_player(connect.pid2);
        close_player_sockets(&connect);
        return match;
    }

    /*      HELLO STUFF         */
    // recv hello message from player1 and player2
    p1_status = recv_message(connect.player1_desc, msg1);
    p2_status = recv_message(connect.player2_desc, msg2);
    status = check_return(&match, p1_status, p2_status);
    if (status)
    {
        kill_player(connect.pid1);
        kill_player(connect.pid2);
        close_player_sockets(&connect);
        return match;
    }

    /* Begin UCI */
    // send and recv UCI
    char msg[MAX_MSG_SIZE];
    snprintf(msg, sizeof(msg), "uci");
    p1_status = send_message(connect.player1_desc, msg);
    p2_status = send_message(connect.player2_desc, msg);
    status = check_return(&match, p1_status, p2_status);
    if (status)
    {
        kill_player(connect.pid1);
        kill_player(connect.pid2);
        close_player_sockets(&connect);
        return match;
    }

    // recv ai name
    p1_status = recv_message(connect.player1_desc, msg1);
    p2_status = recv_message(connect.player2_desc, msg2);
    status = check_return(&match, p1_status, p2_status);
    if (status)
    {
        kill_player(connect.pid1);
        kill_player(connect.pid2);
        close_player_sockets(&connect);
        return match;
    }
    parse_ai_name_msg(msg1, match.player1.ai_name);
    parse_ai_name_msg(msg2, match.player2.ai_name);

    // recv author names
    p1_status = recv_message(connect.player1_desc, msg1);
    p2_status = recv_message(connect.player2_desc, msg2);
    status = check_return(&match, p1_status, p2_status);
    if (status)
    {
        kill_player(connect.pid1);
        kill_player(connect.pid2);
        close_player_sockets(&connect);
        return match;
    }
    parse_author_names_msg(msg1, match.player1.author_name);
    parse_author_names_msg(msg2, match.player2.author_name);

    end = time(NULL);
    match.elapsed_time = end - start;

    kill_player(connect.pid1);
    kill_player(connect.pid2);
    close_player_sockets(&connect);

    return match;
}
void run_contest_2(int board_size, int num_games, Connection connect, string socket_name, vector<tuple<string, string>> &execs, int delay, bool display_now)
{
    vector<ContestPlayer> all_players;   // used for the leaderboard.
    vector<ContestPlayer> alive_players; // used to store players that are still in the contest, but aren't in a game currently.
    vector<ContestPlayer> dead_players;  // used to store players that no longer play the contest.
}

int check_return(Match *match, ErrorNum p1_status, ErrorNum p2_status)
{
    int status = 0;
    if (p1_status != NO_ERR)
    { // player1 is wrong
        if (p2_status != NO_ERR)
        { // both players are wrong, tie
            match->player1.ties++;
            match->player2.ties++;
            status = -3;
        }
        else
        { // only player1 is wrong
            match->player1.losses++;
            match->player2.wins++;
            status = -1;
        }
    }
    else if (p2_status != NO_ERR)
    { // only player2 is wrong
        match->player1.wins++;
        match->player2.losses++;
        status = -2;
    }
    match->player1.error = p1_status;
    match->player2.error = p2_status;
    return status;
}