#include <sprite.h>
#include <graphics.h>
#include <globals.h>

Sprite::Sprite(){
    this->_boundingBox = Rectangle(0,0,0,0);
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

    this->_boundingBox = Rectangle(this->_x, this->_y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}
Sprite::~Sprite(){

}
void Sprite::update(){
    this->_boundingBox.set_x(this->_x);
    this->_boundingBox.set_y(this->_y);
}

const Rectangle Sprite::getBoundingBox() const {
    return this->_boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
    int amountRight, amountLeft, amountTop, amountBottom;
    amountRight = this->getBoundingBox().getRight() - other.getLeft();
    amountLeft = other.getRight() - this->getBoundingBox().getLeft();
    amountTop = other.getBottom() - this->getBoundingBox().getTop();
    amountBottom = this->getBoundingBox().getBottom() - other.getTop();

    int vals[4] = { abs(amountRight), abs(amountLeft), abs(amountTop), abs(amountBottom)};
    int lowest = vals[0];
    for (int i=0; i<4; i++){
        if (vals[i] < lowest) lowest = vals[i];
    }

    return
        lowest == abs(amountRight) ? sides::RIGHT :
        lowest == abs(amountLeft) ? sides::LEFT :
        lowest == abs(amountTop) ? sides::TOP :
        lowest == abs(amountBottom) ? sides::BOTTOM :
        sides::NONE;
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