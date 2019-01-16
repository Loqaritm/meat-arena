#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <animated_sprite.h>

class Graphics;

class Player : public AnimatedSprite{
public:
    Player();
    Player(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
            float posX, float posY, int player_fd = 0);
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
    
    // a function that calculates both the jumps and the falls
    void jumpingAndFalling();

    // makes the player fall down
    void falling();

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();

    void handleTileCollisions(std::vector<Rectangle> &others);
    void handlePlayerCollisions(Rectangle &other);

    bool isDead();
    void respawn(std::vector<Vector2> respawnPoints);

    int get_player_fd();
    void set_player_fd(int fd);
    void set_position(Vector2 position);

private:
    float _dx, _dy, _velocityY;
    float _jumping_height_now;
    bool _readyToJump;
    bool _jumping;
    bool _dead;
    Direction _facing;
    int _player_fd;
};

#endif