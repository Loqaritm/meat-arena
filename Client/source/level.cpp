#include <level.h>
#include <graphics.h>
#include <tile.h>
#include <tinyxml2.h>

#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

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
    // // temp
    // this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
    //     graphics.loadImage("Client/Content/Backgrounds/bkFog.png"));

    // this->_size = Vector2(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);

    XMLDocument doc;
    std::stringstream ss;
    ss << "Client/Content/Maps/" << mapName << ".tmx";
    doc.LoadFile(ss.str().c_str());

    XMLElement* mapNode = doc.FirstChildElement("map");

    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width,height);

    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2(tileWidth,tileHeight);

    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL){
        while (pTileset){
            int firstgid;
            const char* source = pTileset->Attribute("source");

            std::stringstream ss;
            // ss << "Client/Content/Maps" << source;
            // to jest tutaj temp dlatego że najpierw trzeba odniesc sie do Maps/cos.xml a potem dopiero stamtad do cos.png w tilesets
            // DO POPRAWIENIA
            ss << "Client/Content/Tilesets/PrtMimi.png";
            printf(ss.str().c_str());
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(),graphics.loadImage(ss.str()));
            this->_tileSets.push_back(Tileset(texture,firstgid));

            pTileset = pTileset->NextSiblingElement("tileset");
        }
    } 

    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != NULL){
        while(pLayer){
            XMLElement* pData = pLayer->FirstChildElement("data");
            if(pData!=NULL){
                while(pData){
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if(pTile!=NULL){
                        int tileCounter = 0;
                        while(pTile){
                            if (pTile->Attribute("gid")==NULL){
                                tileCounter++;
                            }
                            else{
                                int gid = pTile->IntAttribute("gid");
                                Tileset tls;
                                for (int i=0; i<this->_tileSets.size(); i++){
                                    if(this->_tileSets[i].firstGid <= gid){
                                        tls = this->_tileSets.at(i);
                                        break;
                                    }
                                }
                                if (tls.firstGid == -1){
                                    //not recognised tileset
                                    tileCounter++;
                                }
                                else{
                                    int xx, yy;
                                    xx = tileCounter % width;
                                    xx *= tileWidth;
                                    yy = tileHeight * (tileCounter/width);
                                    Vector2 finalTilePosition = Vector2(xx,yy);
                                    
                                    int tilesetWidth, tilesetHeight;
                                    SDL_QueryTexture(tls.texture,NULL, NULL, &tilesetWidth, &tilesetHeight);
                                    int tsxx, tsyy;
                                    tsxx = gid % (tilesetWidth / tileWidth) - 1;
                                    tsxx *= tileWidth;
                                    tsyy = gid / (tilesetWidth/tileWidth);
                                    tsyy*=tileHeight;
                                    Vector2 finalTilesetPosition = Vector2(tsxx,tsyy);
                                    
                                    Tile tile(tls.texture, Vector2(tileWidth, tileHeight),finalTilesetPosition,finalTilePosition);
                                    this->_tileList.push_back(tile);
                                    tileCounter++;
                                }

                            }
                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    pData = pData->NextSiblingElement("data");
                }
            }
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }

    // start of collision rectangles parsing
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if(pObjectGroup!=NULL){
        while(pObjectGroup){
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if (ss.str() == "collisionrectangles"){
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject!=NULL){
                    while(pObject){
                        
                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");
                        this->_collisionRectangles.push_back(Rectangle(std::floor(x) * globals::SPRITE_SCALE,
                            std::floor(y) * globals::SPRITE_SCALE,
                            std::ceil(width) * globals::SPRITE_SCALE,
                            std::ceil(height) * globals::SPRITE_SCALE));

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            // else other groups
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Level::update(float elapsedTime){}

void Level::draw(Graphics &graphics){
    // SDL_Rect sourceRect = {0,0,320,240};
    // SDL_Rect destRect = {0,0,this->_size.x, this->_size.y};
    // graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
    for (int i=0; i<this->_tileList.size(); i++){
        this->_tileList.at(i).draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other){
    std::vector<Rectangle> temp;
    for (int i=0; i< this->_collisionRectangles.size(); i++){
        if (this->_collisionRectangles.at(i).collidesWith(other)){
            temp.push_back(this->_collisionRectangles.at(i));
        }
    }
    return temp;
}