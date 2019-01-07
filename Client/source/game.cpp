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
    TTF_Init();
    std::srand(SDL_GetTicks());
    this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
    Graphics graphics;
    Input input;
    SDL_Event event;


    // just a test to show that you cen get screen size TODO: using it to scale the graphics
    int width, height;
    graphics.getWindowSize(width, height);
    printf(std::to_string(width).c_str());
    printf(std::to_string(height).c_str());

    // this->_player1 = Player(graphics, "Client/Content/Sprites/MyChar.png", 0, 0, 16, 16, 100, 100);
    this->_player1 = Player(graphics, "Client/Content/Sprites/meat.png", 0, 0, 16, 16, 100, 100);
    this->_player2 = Player(graphics, "Client/Content/Sprites/triangle.png", 0, 0, 16, 16, 150, 100);
    this->_player3 = Player(graphics, "Client/Content/Sprites/circle.png", 0, 0, 16, 16, 200, 100);
    this->_player1.playAnimation("IdleRight");
    this->_player2.playAnimation("IdleRight");
    this->_player3.playAnimation("IdleRight");

    //initialising vector of players
    // this->_players.clear();
    this->_players.push_back(&this->_player1);
    this->_players.push_back(&this->_player2);
    this->_players.push_back(&this->_player3);

    this->_hud = Hud();
    this->_level = Level("map1", Vector2(100,100), graphics);

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

        //player 1 inputs
        if (! (input.isKeyHeld(SDL_SCANCODE_LEFT) & input.isKeyHeld(SDL_SCANCODE_RIGHT))){
            if(input.isKeyHeld(SDL_SCANCODE_LEFT)){
                this->_player1.moveLeft();
            }
            if(input.isKeyHeld(SDL_SCANCODE_RIGHT)){
                this->_player1.moveRight();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_UP)){
            this->_player1.jump();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_LEFT)){
            this->_player1.stopMoving();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_RIGHT)){
            this->_player1.stopMoving();
        }


        //player 2 inputs
        if (! (input.isKeyHeld(SDL_SCANCODE_A) & input.isKeyHeld(SDL_SCANCODE_D))){
            if(input.isKeyHeld(SDL_SCANCODE_A)){
                this->_player2.moveLeft();
            }
            if(input.isKeyHeld(SDL_SCANCODE_D)){
                this->_player2.moveRight();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_W)){
            this->_player2.jump();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_A)){
            this->_player2.stopMoving();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_D)){
            this->_player2.stopMoving();
        }

        //player 3 inputs
        if (! (input.isKeyHeld(SDL_SCANCODE_J) & input.isKeyHeld(SDL_SCANCODE_L))){
            if(input.isKeyHeld(SDL_SCANCODE_J)){
                this->_player3.moveLeft();
            }
            if(input.isKeyHeld(SDL_SCANCODE_L)){
                this->_player3.moveRight();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_I)){
            this->_player3.jump();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_J)){
            this->_player3.stopMoving();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_L)){
            this->_player3.stopMoving();
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
    this->_level.draw(graphics);
    this->_player1.draw(graphics);
    this->_player2.draw(graphics);
    this->_player3.draw(graphics);
    // this->_hud.draw(graphics, this->_player1.get_x(), this->_player1.get_y());
    this->_hud.draw(graphics, _player1.getCurrentAnimation());
    graphics.flip();
}

void Game::update(float elapsedTime){
    _player1.update(elapsedTime);
    _player2.update(elapsedTime);
    _player3.update(elapsedTime);
    _level.update(elapsedTime);

    std::vector<Rectangle> otherRectangles;
    otherRectangles = this->_level.checkTileCollisions(this->_player1.getBoundingBox());
    if (otherRectangles.size() > 0){
        this->_player1.handleTileCollisions(otherRectangles);
    }
    otherRectangles = this->_level.checkTileCollisions(this->_player2.getBoundingBox());
    if (otherRectangles.size() > 0){
        this->_player2.handleTileCollisions(otherRectangles);
    }
    otherRectangles = this->_level.checkTileCollisions(this->_player3.getBoundingBox());
    if (otherRectangles.size() > 0){
        this->_player3.handleTileCollisions(otherRectangles);
    }



    //checking collisions
    std::vector<Player*>::iterator iter1;
    std::vector<Player*>::iterator iter2; 

    for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
        for (iter2 = this->_players.begin(); iter2 != this->_players.end(); iter2++){
            if (iter1 != iter2){
                if((*iter1)->getBoundingBox().collidesWith((*iter2)->getBoundingBox())){
                    Rectangle other = (*iter2)->getBoundingBox();
                    (*iter1)->handlePlayerCollisions(other);
                }
            }
        }
    }

    for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
        if((*iter1)->isDead()){
            (*iter1)->respawn(this->_level.getRespawnPoints());
        }
    }


    SDL_Delay(globals::MAX_FRAME_TIME - elapsedTime);
}