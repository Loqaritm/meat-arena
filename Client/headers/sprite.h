#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <rectangle.h>
#include "SDL2/SDL_image.h"
#include <globals.h>

class Graphics;

class Sprite{
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
            float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);

    float get_x();
    float get_y();

    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle &other) const;
protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
    float _x, _y;
    Rectangle _boundingBox;
private:
};

#endif