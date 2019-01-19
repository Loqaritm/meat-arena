#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>;

namespace globals{
    // const int SCREEN_WIDTH = 640;
    const int SCREEN_WIDTH = 768;
    const int SCREEN_HEIGHT = 480;

    const float SPRITE_SCALE = 2.0f;

    const int FPS = 60;
    const int MAX_FRAME_TIME = 1000/60;

    const std::string SERVER_IP = "localhost";
    const std::string SERVER_PORT = "4200";
}
namespace sides{
    enum Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    const inline Side getOppositeSide(Side side) {
        return
            side == TOP ? BOTTOM :
            side == BOTTOM ? TOP :
            side == LEFT ? RIGHT :
            side == RIGHT ? LEFT :
            NONE;
    }
}

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Vector2 {
    int x,y;
    Vector2() :
        x(0), y(0) {}

    Vector2(int x, int y) :
        x(x), y(y) {}

    Vector2 zero(){
        Vector2(0,0);
    }
};

#endif