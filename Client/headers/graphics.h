#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include "SDL2/SDL_image.h"

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
    public:
        Graphics();
        ~Graphics();
        SDL_Surface* loadImage(const std::string &filepath);
        void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, bool mirror = false);
        
        //renders everything to the screen
        void flip();

        //clears the screen
        void clear();

        SDL_Renderer* getRenderer() const;

        void getWindowSize(int &width, int &height);
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif