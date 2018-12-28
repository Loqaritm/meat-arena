#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <globals.h>

class Rectangle{
public:
    Rectangle() {}
    Rectangle(int x, int y, int width, int height, bool isPlayer = false) :
        _x(x),
        _y(y),
        _width(width),
        _height(height),
        _isPlayer(isPlayer)
        {}

    const int getCenterX() const {
        return this->_x + this->_width / 2;
    }
    const int getCenterY() const {
        return this->_y + this->_height / 2;
    }
    const Vector2 getCenter() const {
        return Vector2(this->getCenterX(), this->getCenterY());
    }
    const int getLeft() const { return this->_x; }
    const int getRight() const { return this->_x + this->_width; }
    const int getTop() const { return this->_y; }
    const int getBottom() const { return this->_y + this->_height; }

    const int getWidth() const { return this->_width; }
    const int getHeight() const { return this->_height; }

    const int getSide(const sides::Side side) const {
        return
            side == sides::LEFT ? this->getLeft() :
            side == sides::RIGHT ? this->getRight() :
            side == sides::TOP ? this->getTop() :
            side == sides::BOTTOM ? this->getBottom() :
            -1;
    }

    const bool collidesWith(const Rectangle &other) const {
        return
            this->getRight() >= other.getLeft() &&
            this->getLeft() <= other.getRight() &&
            this->getBottom() >= other.getTop() &&
            this->getTop() <= other.getBottom();
    }

    const bool isValidRectangle() const {
        return (this->_x>=0 && this->_y>=0 && this->_width>=0 && this->_height>=0);
    }

    void set_x(int x){
        this->_x = x;
    }
    void set_y(int y){
        this->_y = y;
    }

private:
    int _x, _y, _width, _height;
    bool _isPlayer;
};

#endif