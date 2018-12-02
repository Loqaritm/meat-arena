#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <sprite.h>
#include <globals.h>
#include <string>
#include <map>
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filepath, int sourceX, int sourceY, int width, int height,
            float posX, float posY, float timeToUpdate);

    void playAnimation(std::string animation, bool once = false);

    void update(int elapsedTime);

    void draw(Graphics &graphics, int x, int y);

    virtual void setupAnimations();

protected:
    bool _currentAnimationOnce;
    double _timeToUpdate;
    std::string _currentAnimation;

    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, bool mirror = false);

    void resetAnimation();

    void stopAnimation();

    void setVisible(bool visible);

    virtual void animationDone(std::string currentAnimation);

private:
    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;
    std::map<std::string, bool> _isAnimationMirrored;

    int _frameIndex;
    double _timeElapsed;
    bool _visible;
};

#endif