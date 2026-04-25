#include "Player.h"
int Player::play_match(char *socket_path, const char *ai_name, const char *author_names)
{
    if (connect_to_socket(socket_path) == -1)
        return -1;

    // send hello message, message gets discarded
    snprintf(msg, sizeof(msg), "%s", "hello");
    if (send_msg() == -1)
        return -1;

    // recv uci message
    if (recv_msg() == -1)
        return -1;
    if (strcmp(msg, "uci") != 0)
        return -1;

    // send ai_name
    snprintf(msg, sizeof(msg), "id name %s", ai_name);
    if (send_msg() == -1)
        return -1;
    // send author_names
    snprintf(msg, sizeof(msg), "id author %s", author_names);
    if (send_msg() == -1)
        return -1;

    // recv setoptions
    while (recv_msg() != -1)
    {
        if (strcmp(msg, "isready") == 0)
            break;
        if (recv_msg() == -1)
            return -1;
        string msg_str = msg;
        vector<string> tokens = separate_string(msg);
        if (tokens[0] != "setoption")
            continue;
        this->setoptions.insert({tokens[2], tokens[4]});
    }

    PlayerNum player;
    int board_size;
    auto player_num_option = setoptions.find("PlayerNum");
    if (player_num_option == setoptions.end())
        return -1;
    player = (PlayerNum)stoi(player_num_option->second);

    auto board_size_option = setoptions.find("board_size");
    if (board_size_option == setoptions.end())
        return -1;
    board_size = stoi(board_size_option->second);

    return 0;
}
int Player::connect_to_socket(char *socket_path)
{
    sockaddr_un server_sock;
    socklen_t len;
    size_t socket_len;

    // use Unix Domain Socket.
    this->socket_desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (this->socket_desc == -1)
        return -1;

    // bind socket values to the socket file.
    server_sock.sun_family = AF_UNIX;
    memset(server_sock.sun_path, 0, sizeof(server_sock.sun_path));
    socket_len = strlen(socket_path);
    if (socket_len > sizeof(server_sock.sun_path) - 1)
    {
        printf("Player Error: Server socket path too long (line: %d)\n", __LINE__);
        return -1;
    }
    memcpy(server_sock.sun_path, socket_path, socket_len + 1);

    // connect to the socket, create a socket descriptor.
    len = strlen(server_sock.sun_path) + sizeof(server_sock.sun_family);
    // if connection fails, return -1;
    if (connect(this->socket_desc, (sockaddr *)&server_sock, len) == -1)
    {
        printf("Player Error: %s (line: %d)\n", strerror(errno), __LINE__);
        return -1;
    }

    // return 0, successful connection.
    return 0;
}

int Player::send_msg()
{
    if (send(this->socket_desc, this->msg, MAX_MSG_SIZE, 0) == -1)
    {
        printf("Player Error: %s (line: %d)\n", strerror(errno), __LINE__);
        return -1;
    }
    return 0;
}

int Player::recv_msg()
{
    memset(this->msg, 0, MAX_MSG_SIZE);
    if (recv(this->socket_desc, this->msg, MAX_MSG_SIZE, 0) == -1)
    {
        printf("Player Error: %s (line: %d)\n", strerror(errno), __LINE__);
    }
    return 0;
}

vector<string> Player::separate_string(const string &str)
{
    istringstream iss(str);
    vector<string> words;
    string word;

    while (iss >> word)
    {
        words.push_back(word);
    }

    return words;
}