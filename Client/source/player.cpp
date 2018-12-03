#include <player.h>
#include <graphics.h>

namespace player_constants {
    const float WALK_SPEED = 0.2f;
}

Player::Player(){}

Player::Player(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
            float posX, float posY) :
    AnimatedSprite(graphics, filepath, 0,0,16,16, posX,posY, globals::MAX_FRAME_TIME*10)
    {
        graphics.loadImage(filepath);
        this->setupAnimations();
    }

void Player::setupAnimations(){
    this->addAnimation(3,0,0,"RunLeft",16,16,Vector2(0,0));
    this->addAnimation(3,0,0,"RunRight",16,16,Vector2(0,0),true);
    this->addAnimation(1,2,0,"IdleLeft",16,16,Vector2(0,0));
    this->addAnimation(1,2,0,"IdleRight",16,16,Vector2(0,0), true);
}

void Player::animationDone(std::string currentAnimation){

}

void Player::moveLeft(){
    this->_dx = -player_constants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->_facing=LEFT;
}

void Player::moveRight(){
    this->_dx = player_constants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->_facing=RIGHT;
}

void Player::stopMoving(){
    this->_dx=0.0f;
    if(this->_facing==LEFT) this->playAnimation("IdleLeft");
    if(this->_facing==RIGHT) this->playAnimation("IdleRight");
}

void Player::update(float elapsedTime){
    //move by _dx
    this->_x+=this->_dx * elapsedTime;

    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics){
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}

