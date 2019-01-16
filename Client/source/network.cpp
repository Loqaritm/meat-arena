#include <network.h>
#include <game.h>
#include <error.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <sstream>
#include <fcntl.h>


Network::Network(){

}

Network::~Network(){

}

void Network::set_socket_nonblocking(int sockfd){
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
}

int Network::connect_to_server(Game &game){
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_TCP;
    addrinfo *resolved;
    if(int err = getaddrinfo(globals::SERVER_IP.c_str(), globals::SERVER_PORT.c_str(), &hints, &resolved)){
        error(1,0, "Error connecting to server", gai_strerror(err));
        printf("Error connecting to server. \n");
    }

    int sockfd = socket(resolved->ai_family, resolved->ai_socktype, resolved->ai_protocol);
    connect(sockfd, resolved->ai_addr, resolved->ai_addrlen);
    char conn_response[3];
    read(sockfd, conn_response, sizeof(conn_response));

    std::stringstream ss;
    ss << conn_response[0] << conn_response[1];
    int temp_fd = std::stoi(ss.str());
    ss.str("");
    ss << conn_response[2];
    int temp_number = std::stoi(ss.str());

    if(temp_fd == 0){
        printf("Server full, try again later. \n");
        return 0;
    }
    else{
        game.my_fd = temp_fd;
        game.my_number = temp_number;
        printf("%d\n",temp_fd);
        printf("%d\n",temp_number);
    }
    return sockfd;
}

int Network::get_game_state(Game &game, int sockfd){

    char gamestate_response[54];
    // 10 timestamp
    // 2 playerfd
    // 2 punkty
    // 6 pozycja
    // 1 player_number

    int count = read(sockfd, gamestate_response, sizeof(gamestate_response));
    
    if(count > 0){
        std::stringstream ss;
        ss.str("");
        for(int i = 0; i< 10; i++){
            ss << gamestate_response[i];
        }
        game.timestamp = std::stoi(ss.str());
        
        for(int i=0; i<4; i++){
            ss.str("");
            ss << gamestate_response[10 + 11*i + 10];
            int player_id = std::stoi(ss.str());

            ss.str("");
            ss << gamestate_response[10+11*i];
            ss << gamestate_response[10+11*i + 1];
            game.player_fds[player_id] = stoi(ss.str());

            ss.str("");
            ss << gamestate_response[10+11*i + 2];
            ss << gamestate_response[10+11*i + 3];
            game.player_points[player_id] = stoi(ss.str());

            ss.str("");
            ss << gamestate_response[10+11*i + 4];
            ss << gamestate_response[10+11*i + 5];
            ss << gamestate_response[10+11*i + 6];
            game.player_positions[player_id].x = stoi(ss.str());

            ss.str("");
            ss << gamestate_response[10+11*i + 7];
            ss << gamestate_response[10+11*i + 8];
            ss << gamestate_response[10+11*i + 9];
            game.player_positions[player_id].y = stoi(ss.str());
        }
    }
}

void intToStr(int num, std::stringstream& ss){
    if(num < 100) ss<<0;
    if(num < 10)ss<<0;
    ss<<num;
}

int Network::send_game_state(Game &game, int sockfd){
    std::stringstream ss;
    ss << time(NULL);
    intToStr((int)game.player_positions[game.my_number].x, ss);
    intToStr((int)game.player_positions[game.my_number].y, ss); 
    ss << "00";
    printf(ss.str().c_str());
    printf("\n");
    write(sockfd, ss.str().c_str(), strlen(ss.str().c_str()));
}