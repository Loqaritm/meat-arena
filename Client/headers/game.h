#ifndef GAME_H
#define GAME_H

#include <player.h>
#include <hud.h>
#include <level.h>
#include <vector>

class Graphics;

class Game{
public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    Player _player1;
    Player _player2;
    std::vector <Player*> _players;
    Hud _hud;
    Level _level;
};

#endif