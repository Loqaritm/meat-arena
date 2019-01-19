#include <graphics.h>
#include <globals.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
/** Graphics class
 *  All information dealing with graphics for the game
 **/

Graphics::Graphics(){
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,globals::SCREEN_HEIGHT,0,&this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Meat Arena");
}

Graphics::~Graphics(){
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

// void Graphics::maximizeWindow(){
//     SDL_MaximizeWindow(this->_window);
// }


//probably wont work
void Graphics::getWindowSize(int &width, int &height){
    SDL_GetWindowSize(this->_window, &width, &height);
}

SDL_Surface* Graphics::loadImage(const std::string &filepath){
    //check if loaded
    if (this->_spriteSheets.count(filepath) == 0){
        this->_spriteSheets[filepath] = IMG_Load(filepath.c_str());
    }
    return _spriteSheets[filepath];
}

void Graphics::blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, bool mirror){
    
    if (mirror){
        SDL_RenderCopyEx(this->_renderer, source, sourceRectangle, destinationRectangle,0,NULL,SDL_FLIP_HORIZONTAL);
    }
    else{
        SDL_RenderCopyEx(this->_renderer, source, sourceRectangle, destinationRectangle,0,NULL,SDL_FLIP_NONE);
    }
}

void Graphics::flip(){
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear(){
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->_renderer;

}