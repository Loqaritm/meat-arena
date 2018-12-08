#include <hud.h>
#include <graphics.h>
#include <string>

Hud::Hud(){
    this->sans = TTF_OpenFont("Client/Content/Fonts/FreeSans.ttf", 24);
    // if (this->sans == NULL) printf("NIE DZIALA FONT");
    this->color = {255,255,255,0};
    this->_sourceRect.x = 0;
    this->_sourceRect.y = 0;
    this->_sourceRect.w = 100;
    this->_sourceRect.h = 100;

}

void Hud::draw(Graphics &graphics, float x, float y){
    std::string text = "Pos X: " + std::to_string(x) + " Pos Y: "+std::to_string(y);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->sans, text.c_str(), this->color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfaceMessage);
    this->_sourceRect.w=surfaceMessage->w;
    this->_sourceRect.h=surfaceMessage->h;
    SDL_FreeSurface(surfaceMessage);
    SDL_RenderCopy(graphics.getRenderer(), Message, NULL, &this->_sourceRect);
    SDL_DestroyTexture(Message);
}

void Hud::draw(Graphics &graphics, std::string currentAnimationName){
    std::string text = "Current animation: " + currentAnimationName;
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->sans, text.c_str(), this->color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfaceMessage);
    this->_sourceRect.w=surfaceMessage->w;
    this->_sourceRect.h=surfaceMessage->h;
    SDL_FreeSurface(surfaceMessage);
    SDL_RenderCopy(graphics.getRenderer(), Message, NULL, &this->_sourceRect);
    SDL_DestroyTexture(Message);
}