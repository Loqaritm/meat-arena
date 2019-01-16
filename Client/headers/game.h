#ifndef GAME_H
#define GAME_H

#include <player.h>
#include <hud.h>
#include <level.h>
#include <vector>

class Graphics;
class Network;

class Game{
public:
    Game();
    ~Game();
    int player_fds[4];
    int timestamp;
    int player_points[4];
    Vector2 player_positions[4];
    int my_number;
    int my_fd;

private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    void network_update(Network &network, int sockfd);
    Player _player1;
    Player _player2;
    Player _player3;
    Player _player4;
    std::vector <Player*> _players;
    Hud _hud;
    Level _level;
};

#endif