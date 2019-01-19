#include "SDL2/SDL.h"
#include <game.h>
#include <graphics.h>
#include <input.h>
#include <globals.h>
#include <network.h>
#include <thread>
#include <sstream>


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

    // network part
    Network network;
    int sockfd;
    if (sockfd = network.connect_to_server(*this)){
        printf("connected to server \n");
    }
    else printf("something went wrong (from game class) \n");
    network.get_game_state(*this, sockfd);
    network.set_socket_nonblocking(sockfd);

    // this->network_update(network, sockfd);
    // std::thread t1(network_update, network, sockfd);
    // std::thread t1(&Game::network_update, this, network, sockfd);

    // this->_player1 = Player(graphics, "Client/Content/Sprites/MyChar.png", 0, 0, 16, 16, 100, 100);
    this->_player1 = Player(graphics, "Client/Content/Sprites/meat.png", 0, 0, 16, 16, 100, 100);
    this->_player2 = Player(graphics, "Client/Content/Sprites/triangle.png", 0, 0, 16, 16, 150, 100);
    this->_player3 = Player(graphics, "Client/Content/Sprites/circle.png", 0, 0, 16, 16, 200, 100);
    this->_player4 = Player(graphics, "Client/Content/Sprites/cat.png", 0, 0, 16, 16, 250, 100);

    this->_player1.playAnimation("IdleRight");
    this->_player2.playAnimation("IdleRight");
    this->_player3.playAnimation("IdleRight");
    this->_player4.playAnimation("IdleRight");

    //initialising vector of players
    // this->_players.clear();
    this->_players.push_back(&this->_player1);
    this->_players.push_back(&this->_player2);
    this->_players.push_back(&this->_player3);
    this->_players.push_back(&this->_player4);

    this->_hud = Hud();
    this->_level = Level("map1", Vector2(100,100), graphics);

    int LAST_UPDATE_TIME=SDL_GetTicks();
    int LAST_WRITE_TIME=SDL_GetTicks();

    
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
                // this->_player1.moveLeft();
                this->_players.at(this->my_number)->moveLeft();
            }
            if(input.isKeyHeld(SDL_SCANCODE_RIGHT)){
                // this->_player1.moveRight();
                this->_players.at(this->my_number)->moveRight();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_UP)){
            // this->_player1.jump();
            this->_players.at(this->my_number)->jump();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_LEFT)){
            // this->_player1.stopMoving();
            this->_players.at(this->my_number)->stopMoving();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_RIGHT)){
            // this->_player1.stopMoving();
            this->_players.at(this->my_number)->stopMoving();
        }

        /*
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

        //player 4 inputs
        if (! (input.isKeyHeld(SDL_SCANCODE_KP_4) & input.isKeyHeld(SDL_SCANCODE_KP_6))){
            if(input.isKeyHeld(SDL_SCANCODE_KP_4)){
                this->_player4.moveLeft();
            }
            if(input.isKeyHeld(SDL_SCANCODE_KP_6)){
                this->_player4.moveRight();
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_KP_8)){
            this->_player4.jump();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_KP_4)){
            this->_player4.stopMoving();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_KP_6)){
            this->_player4.stopMoving();
        }
        */

        this->network_update(network, sockfd);

        const int CURRENT_TIME = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME, globals::MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME;

        this->draw(graphics);
        if(CURRENT_TIME - LAST_WRITE_TIME > globals::MAX_FRAME_TIME){
            int kill_fd = this->_players.at(this->my_number)->killedWho();
            network.send_game_state(*this, sockfd, kill_fd);
            LAST_WRITE_TIME = CURRENT_TIME;
        }
    }
}

void Game::network_update(Network &network, int sockfd){
    network.get_game_state(*this, sockfd);

    int i = 0;
    std::vector<Player*>::iterator iter1;
    for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
        if(i != my_number){
            (*iter1)->set_position(this->player_positions[i]);
        }
        (*iter1)->set_player_fd(this->player_fds[i]);
        i++;
    }

}

void Game::draw(Graphics &graphics){
    graphics.clear();
    this->_level.draw(graphics);
    std::vector<Player*>::iterator iter1;
    for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
        if((*iter1)->get_player_fd() != 0){
            (*iter1)->draw(graphics);
            // printf("%d\n",(*iter1)->get_player_fd());
        }
    }

    this->_hud.drawPoints(graphics, this->player_points);
    graphics.flip();
}

void Game::update(float elapsedTime){
    std::vector<Player*>::iterator iter1;
    std::vector<Player*>::iterator iter2;

    // _player1.update(elapsedTime);
    // _player2.update(elapsedTime);
    // _player3.update(elapsedTime);
    // _player4.update(elapsedTime);

    int i = 0;
    for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
        if(i == this->my_number){
            (*iter1)->update(elapsedTime);
            this->player_positions[this->my_number].x = (int)((*iter1)->get_x());
            this->player_positions[this->my_number].y = (int)((*iter1)->get_y());
        }
        else{
            (*iter1)->update_bounding_box();
        }
        i++;
    }

    // this->_players.at(this->my_number)->update(elapsedTime);
    // this->player_positions[this->my_number].x = (int)(this->_players.at(this->my_number)->get_x());
    // this->player_positions[this->my_number].y = (int)(this->_players.at(this->my_number)->get_y());


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
    otherRectangles = this->_level.checkTileCollisions(this->_player4.getBoundingBox());
    if (otherRectangles.size() > 0){
        this->_player4.handleTileCollisions(otherRectangles);
    }




    //checking collisions
    for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
        for (iter2 = this->_players.begin(); iter2 != this->_players.end(); iter2++){
            if (iter1 != iter2){
                if((*iter1)->getBoundingBox().collidesWith((*iter2)->getBoundingBox())){
                    Rectangle other = (*iter2)->getBoundingBox();
                    // Player player = **iter2;
                    (*iter1)->handlePlayerCollisions(**iter2);
                }
            }
        }
    }

    // for (iter1 = this->_players.begin(); iter1 != this->_players.end(); iter1++){
    //     if((*iter1)->isDead()){
    //         (*iter1)->respawn(this->_level.getRespawnPoints());
    //     }
    // }
    if (this->_players.at(this->my_number)->isDead()){
        this->_players.at(this->my_number)->respawn(this->_level.getRespawnPoints());
    }


    // SDL_Delay(globals::MAX_FRAME_TIME - elapsedTime);
}