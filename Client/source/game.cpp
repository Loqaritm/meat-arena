#include "SDL2/SDL.h"
#include <game.h>
#include <graphics.h>
#include <input.h>
/** Game class
 *  Main game loop
 * 
 */

namespace{
    const int FPS = 60;
    const int MAX_FRAME_TIME = 1000/60;
}


Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
    Graphics graphics;
    Input input;
    SDL_Event event;

    int LAST_UPDATE_TIME=SDL_GetTicks();


    //main loop
    while(true){
        input.beginNewFrame();

        if (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                if(event.key.repeat == 0){
                    input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP){
                input.keyUpEvent(event);
            }

            if (event.type == SDL_QUIT){
                return;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
            return;
        }

        const int CURRENT_TIME = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME;


    }
}

void Game::draw(Graphics &graphics){

}

void Game::update(float elapsedTime){

}
