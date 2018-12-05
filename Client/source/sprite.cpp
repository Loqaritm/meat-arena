#include <sprite.h>
#include <graphics.h>
#include <globals.h>

Sprite::Sprite(){

}
Sprite::Sprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
                float posX, float posY) : 
                _x(posX),
                _y(posY)
{
    this->_sourceRect.x=sourceX;
    this->_sourceRect.y=sourceY;
    this->_sourceRect.w=width;
    this->_sourceRect.h=height;
    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(),graphics.loadImage(filepath));
    if (this->_spriteSheet == NULL){
        printf("\nError in loading image\n");
    }
}
Sprite::~Sprite(){

}
void Sprite::update(){

}
void Sprite::draw(Graphics &graphics, int x, int y){
    SDL_Rect destinationRectangle = {x,y,this->_sourceRect.w * globals::SPRITE_SCALE ,this->_sourceRect.h * globals::SPRITE_SCALE};
    graphics.blitSurface(this->_spriteSheet,&this->_sourceRect,&destinationRectangle);
}

float Sprite::get_x(){
    return this->_x;
}
float Sprite::get_y(){
    return this->_y;
}