#include <level.h>
#include <graphics.h>

#include <SDL2/SDL.h>

Level::Level(){}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size(Vector2(0,0))
    {
        this->loadMap(mapName, graphics);
    }

Level::~Level(){}

void Level::loadMap(std::string mapName, Graphics &graphics){
    this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
        graphics.loadImage("Client/Content/Backgrounds/bkFog.png"));

    this->_size = Vector2(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
}

void Level::update(float elapsedTime){}

void Level::draw(Graphics &graphics){
    SDL_Rect sourceRect = {0,0,320,240};
    SDL_Rect destRect = {0,0,this->_size.x, this->_size.y};
    graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
}