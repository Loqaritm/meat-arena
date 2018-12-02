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

    this->_player = AnimatedSprite(graphics,"Client/Content/Sprites/MyChar.png",0, 0, 16, 16, 100, 100, MAX_FRAME_TIME*10);
    this->_player.setupAnimations();
    this->_player.playAnimation("RunLeft");


    int LAST_UPDATE_TIME=SDL_GetTicks();


    //main loop
    while(true){
        input.beginNewFrame();

        if (SDL_PollEvent(&event)){  //used to be SDL_PollEvent, but WaitEvent seems much more CPU-friendly
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
        if (! (input.isKeyHeld(SDL_SCANCODE_LEFT) & input.isKeyHeld(SDL_SCANCODE_RIGHT))){
            if(input.isKeyHeld(SDL_SCANCODE_LEFT)){
                this->_player.playAnimation("RunLeft");
            }
            if(input.isKeyHeld(SDL_SCANCODE_RIGHT)){
                this->_player.playAnimation("RunRight");
            }
        }
        if(input.wasKeyReleased(SDL_SCANCODE_LEFT)){
            this->_player.playAnimation("StandLookingLeft");
        }
        if(input.wasKeyReleased(SDL_SCANCODE_RIGHT)){
            this->_player.playAnimation("StandLookingRight");
        }

        const int CURRENT_TIME = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME;

        this->draw(graphics);

    }
}

void Game::draw(Graphics &graphics){
    graphics.clear();
    this->_player.draw(graphics, 100, 100);
    graphics.flip();
}

void Game::update(float elapsedTime){
    _player.update(elapsedTime);
    SDL_Delay(MAX_FRAME_TIME - elapsedTime);
}
