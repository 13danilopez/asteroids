#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

#include "constants.h"

class Bullet
{
protected:
    Vector2 pos;
    Vector2 velocity;
    float angle;
    Color color;

public:
    Bullet();
    Bullet(Vector2 pos, Vector2 velocity, float angle);

    Vector2 getPos();

    void update(float dt);

    void draw();
};

#endif