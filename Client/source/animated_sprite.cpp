#include <animated_sprite.h>
#include <graphics.h>
#include <sprite.h>

AnimatedSprite::AnimatedSprite(){

}
AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
        float posX, float posY, float timeToUpdate) :
        Sprite(graphics,filepath,sourceX,sourceY,width,height,posX,posY),
        _frameIndex(0),
        _timeToUpdate(timeToUpdate),
        _visible(true),
        _currentAnimationOnce(false),
        _currentAnimation(""),
        _timeElapsed(0)
{
    
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, bool mirror){
    std::vector<SDL_Rect> tempRectangles;
    for (int i =0; i<frames; i++){
        SDL_Rect tempRect = {(i+x)*width, y, width, height};
        tempRectangles.push_back(tempRect);
    }
    this->_animations.insert(std::pair<std::string,std::vector<SDL_Rect>>(name, tempRectangles));
    this->_offsets.insert(std::pair<std::string,Vector2>(name, offset));
    this->_isAnimationMirrored.insert (std::pair<std::string,bool>(name,mirror));
}

void AnimatedSprite::resetAnimation(){
    this->_animations.clear();
    this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once){
    this->_currentAnimationOnce=once;
    if (this->_currentAnimation != animation){
        this->_currentAnimation = animation;
        this->_frameIndex = 0;
    }
}

void AnimatedSprite::setVisible(bool visible){
    this->_visible = visible;
}

void AnimatedSprite::stopAnimation(){
    this->_frameIndex = 0;
    this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime){
    Sprite::update();
    this->_timeElapsed+=elapsedTime;
    if (this->_timeElapsed > this->_timeToUpdate){
        this->_timeElapsed -= this->_timeToUpdate;
        if (this->_frameIndex < this->_animations[this->_currentAnimation].size()-1){
            this->_frameIndex ++;
        }
        else{
            if (this->_currentAnimationOnce == true){
                this->setVisible(false);
            }
            this->_frameIndex = 0;
            this->animationDone(this->_currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y){
    if ( this->_visible){
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
        destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
        destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
        destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

        SDL_Rect tempSourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
        graphics.blitSurface(this->_spriteSheet,&tempSourceRect, &destinationRectangle, this->_isAnimationMirrored[this->_currentAnimation]);
    }
}
