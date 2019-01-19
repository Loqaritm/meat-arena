#ifndef NETWORK_H
#define NETWORK_H


class Game;

class Network{
public:
    Network();
    ~Network();

    int connect_to_server(Game &game);
    int get_game_state(Game &game, int sockfd);
    int send_game_state(Game &game, int sockfd, int killfd);
    void set_socket_nonblocking(int sockfd);
};

#endif