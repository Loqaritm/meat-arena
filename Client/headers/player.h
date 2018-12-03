#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <animated_sprite.h>

class Graphics;

class Player : public AnimatedSprite{
public:
    Player();
    Player(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
            float posX, float posY);
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    // moves the player left by -_dx
    void moveLeft();
    // moves the player right by _dx
    void moveRight();
    // stops moving the player and plays idle
    void stopMoving();
    // makes the player jump
    void jump();
    // computes when player is jumping
    void jumping();
    // makes the player fall down
    void falling();

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
private:
    float _dx, _dy;
    float _jumping_height_now;
    bool _readyToJump;
    bool _jumping;
    Direction _facing;
};

#endif