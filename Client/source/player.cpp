#include <player.h>
#include <graphics.h>
#include <globals.h>

namespace player_constants {
    const float WALK_SPEED = 0.2f;
    const float JUMP_SPEED = 0.75f;
    const float ACCELERATION = 0.002f;
    const float MAX_JUMP_HEIGHT = 5.0f * globals::SPRITE_SCALE;
}

Player::Player(){}

Player::Player(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
            float posX, float posY) :
    AnimatedSprite(graphics, filepath, 0,0,16,16, posX,posY, globals::MAX_FRAME_TIME*10),
    _readyToJump(false),
    _jumping(true),
    _jumping_height_now(0.0f)
    {
        graphics.loadImage(filepath);
        this->setupAnimations();
    }

void Player::setupAnimations(){
    // this->addAnimation(3,0,0,"RunLeft",16,16,Vector2(0,0));
    // this->addAnimation(3,0,0,"RunRight",16,16,Vector2(0,0),true);
    // this->addAnimation(1,2,0,"IdleLeft",16,16,Vector2(0,0));
    // this->addAnimation(1,2,0,"IdleRight",16,16,Vector2(0,0), true);
    
    // this->addAnimation(1,0,0,"JumpLeft",16,16,Vector2(0,0));
    // this->addAnimation(1,0,0,"JumpRight",16,16,Vector2(0,0), true);
    // this->addAnimation(1,8,0,"FallLeft",16,16,Vector2(0,0));
    // this->addAnimation(1,8,0,"FallRight",16,16,Vector2(0,0), true);
    this->addAnimation(4,0,0,"RunLeft",16,16,Vector2(0,0));
    this->addAnimation(4,0,0,"RunRight",16,16,Vector2(0,0),true);
    this->addAnimation(1,1,0,"IdleLeft",16,16,Vector2(0,0));
    this->addAnimation(1,1,0,"IdleRight",16,16,Vector2(0,0), true);
    
    this->addAnimation(1,0,16,"JumpLeft",16,16,Vector2(0,0));
    this->addAnimation(1,0,16,"JumpRight",16,16,Vector2(0,0), true);
    this->addAnimation(1,1,16,"JumpLeftApex",16,16,Vector2(0,0));
    this->addAnimation(1,1,16,"JumpRightApex",16,16,Vector2(0,0), true);
    this->addAnimation(1,2,16,"FallLeft",16,16,Vector2(0,0));
    this->addAnimation(1,2,16,"FallRight",16,16,Vector2(0,0), true);

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

void Player::handleTileCollisions(std::vector<Rectangle> &others){
    for (int i=0; i<others.size(); i++){
        sides::Side collisionSide = this->getCollisionSide(others.at(i));
        if(collisionSide != sides::NONE){
            switch(collisionSide){
            case sides::TOP:
                this->_y = others.at(i).getBottom() + 1;
                this->_dy = 0;
                this->_velocityY = 0.0f;
                break;
            case sides::BOTTOM:
                this->_y = others.at(i).getTop() - 1 - this->_boundingBox.getHeight();
                this->_dy = 0;
                this->_jumping = false;
                this->_readyToJump = true;
                this->_velocityY = 0.0f;
                break;
            case sides::LEFT:
                this->_x = others.at(i).getRight() + 1;
                this->_dx = 0;
                break;
            case sides::RIGHT:
                this->_x = others.at(i).getLeft() - 1 - this->_boundingBox.getWidth();
                this->_dx = 0;
                break;
            }
        }
    }
}

void Player::handlePlayerCollisions(Rectangle &other){
    sides::Side collisionSide = this->getCollisionSide(other);
    if(collisionSide != sides::NONE){
        switch(collisionSide){
        case sides::TOP:
            this->_dead = true;
            // this->_x= 100;
            // this->_y = 100;
            break;
        case sides::BOTTOM:
            //add points here
            break;

        //te dwie rzeczy sprawiaja ze sie przepychaja bo koliduja ze soba no nie
        case sides::LEFT:
            this->_x = other.getRight() + 1;
            this->_dx = 0;
            break;
        case sides::RIGHT:
            this->_x = other.getLeft() - 1 - this->_boundingBox.getWidth();
            this->_dx = 0;
            break;
        }
    }
}

void Player::jump(){
    if (this->_readyToJump) {
        this->_jumping = true;
        this->_readyToJump = false;
        this->_velocityY = player_constants::JUMP_SPEED;
        this->_y -= this->_velocityY;
    }
}


void Player::jumpingAndFalling(){

    // bullshit way of fixing things
    // DOESNT WORK
    // if (this->_dy != 0.0f){
    //     this->_facing==LEFT ? this->playAnimation("FallLeft") : this->playAnimation("FallRight");           
    // }

    if (this->_jumping){
        // this->_velocityY -= player_constants::ACCELERATION;
        if (this->_velocityY < 1.0f/4.0f * player_constants::JUMP_SPEED && this->_velocityY > -1.0f/4.0f * player_constants::JUMP_SPEED) 
            this->_facing==LEFT ? this->playAnimation("JumpLeftApex") : this->playAnimation("JumpRightApex");
        else if (this->_velocityY > 0.0f) 
            this->_facing==LEFT ? this->playAnimation("JumpLeft") : this->playAnimation("JumpRight");
        else 
            this->_facing==LEFT ? this->playAnimation("FallLeft") : this->playAnimation("FallRight");           
    }
    // _velocity calculation in update for proper framerate calculation
    this->_dy = -this->_velocityY;
}


void Player::update(float elapsedTime){
    this->jumpingAndFalling();

    this->_x+=this->_dx * elapsedTime;
    this->_y+=this->_dy * elapsedTime;
    // velocity calculation needs to be here to work properly in low framerates
    this->_velocityY -= player_constants::ACCELERATION * elapsedTime;

    if(this->_dy == 0.0f && this->_dx == 0.0f){
        this->stopMoving();
    }

    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics){
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}

bool Player::isDead(){
    return this->_dead;
}

void Player::respawn(std::vector<Vector2> respawnPoints){
    int numberOfRespawnPoints = respawnPoints.size();
    int i = std::rand() % numberOfRespawnPoints;
    Vector2 playerPosAfterRespawn = respawnPoints.at(i);
    this->_x = playerPosAfterRespawn.x;
    this->_y = playerPosAfterRespawn.y;
    this->_dead = false;
}
