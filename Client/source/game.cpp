#include "SDL2/SDL.h"
#include <game.h>
#include <graphics.h>
#include <input.h>
#include <globals.h>
/** Game class
 *  Main game loop
 * 
 */




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

    // this->_player = Player(graphics, "Client/Content/Sprites/MyChar.png", 0, 0, 16, 16, 100, 100);
    this->_player = Player(graphics, "Client/Content/Sprites/meat.png", 0, 0, 16, 16, 100, 100);
    this->_player.playAnimation("IdleRight");


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
                this->_player.moveLeft();
            }
            if(input.isKeyHeld(SDL_SCANCODE_RIGHT)){
                this->_player.moveRight();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_UP)){
            this->_player.jump();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_LEFT)){
            this->_player.stopMoving();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_RIGHT)){
            this->_player.stopMoving();
        }

        const int CURRENT_TIME = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME, globals::MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME;

        this->draw(graphics);

    }
}

void Game::draw(Graphics &graphics){
    graphics.clear();
    this->_player.draw(graphics);
    graphics.flip();
}

void Game::update(float elapsedTime){
    _player.update(elapsedTime);
    SDL_Delay(globals::MAX_FRAME_TIME - elapsedTime);
}
