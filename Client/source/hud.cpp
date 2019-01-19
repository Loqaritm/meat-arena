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

void Hud::drawAt(Graphics &graphics, std::string text, int x, int y){
    // std::string text = "Pos X: " + std::to_string(x) + " Pos Y: "+std::to_string(y);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->sans, text.c_str(), this->color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfaceMessage);
    this->_sourceRect.x=x;
    this->_sourceRect.y=y;
    this->_sourceRect.w=surfaceMessage->w;
    this->_sourceRect.h=surfaceMessage->h;
    SDL_FreeSurface(surfaceMessage);
    SDL_RenderCopy(graphics.getRenderer(), Message, NULL, &this->_sourceRect);
    SDL_DestroyTexture(Message);
}

void Hud::drawPoints(Graphics &graphics, int player_points[]){
    this->color = {242, 6, 6, 0};
    this->drawAt(graphics, "Meaty", 654, 60);
    this->drawAt(graphics, std::to_string(player_points[0]), 690, 90);


    this->color = {27, 246, 8, 0};
    this->drawAt(graphics, "Trigg", 654, 150);
    this->drawAt(graphics, std::to_string(player_points[1]), 690, 180);

    this->color = {242, 212, 13, 0};
    this->drawAt(graphics, "Pip", 654, 240);
    this->drawAt(graphics, std::to_string(player_points[2]), 690, 270);

    this->color = {18, 24, 241, 0};
    this->drawAt(graphics, "Neko", 654, 330);
    this->drawAt(graphics, std::to_string(player_points[3]), 690, 360);
}