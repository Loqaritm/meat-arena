#ifndef HUD_H
#define HUD_H

#include "SDL2/SDL_ttf.h"

#include <sprite.h>

class Hud : public Sprite{
public:
    Hud();
    void drawAt(Graphics &graphics, std::string text, int x, int y);
    void drawPoints(Graphics &graphics, int player_points[]);
private:
    TTF_Font* sans;
    SDL_Color color;
};

#endif