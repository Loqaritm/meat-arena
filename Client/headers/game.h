#ifndef GAME_H
#define GAME_H

#include <animated_sprite.h>

class Graphics;

class Game{
public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    AnimatedSprite _player;
};

#endif