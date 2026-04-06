#include "Player.h"

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