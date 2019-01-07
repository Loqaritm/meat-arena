#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <globals.h>
#include <vector>
#include <tile.h>
#include <rectangle.h>
#include <player.h>

class Graphics;
struct SDL_Texture;
struct Tileset;

class Level{
public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    void update(float elapsedTime);
    void draw(Graphics &graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Vector2> getRespawnPoints();

private:
std::string _mapName;
Vector2 _spawnPoint;
Vector2 _size;
Vector2 _tileSize;
SDL_Texture* _backgroundTexture;
std::vector<Tile> _tileList;
std::vector<Tileset> _tileSets;
std::vector<Rectangle> _collisionRectangles;
std::vector<Vector2> _respawnPoints;

void loadMap(std::string mapName, Graphics &graphics);
};

struct Tileset{
    SDL_Texture* texture;
    int firstGid;

    Tileset(){
        this->firstGid=-1;
    }
    Tileset(SDL_Texture* texture, int firstGid){
        this->texture=texture;
        this->firstGid=firstGid;
    }
};

#endif