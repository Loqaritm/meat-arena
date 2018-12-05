#ifndef HUD_H
#define HUD_H

#include "SDL2/SDL_ttf.h"

#include <sprite.h>

class Hud : public Sprite{
public:
    Hud();
    void draw(Graphics &graphics, float x, float y);
private:
    TTF_Font* sans;
    SDL_Color color;
};

#endif