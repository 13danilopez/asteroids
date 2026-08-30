#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"

#include "constants.h"
#include "aux_functions.h"

class Asteroid
{
protected:
    Vector2 pos;
    Vector2 velocity; // Velocity is constant for asteroids
    float angle;
    float radius;
    int id;

public:
    Asteroid();
    Asteroid(Vector2 pos, Vector2 velocity, float angle, float radius, int id);

    Vector2 getPos();
    Vector2 getVelocity();
    float getRadius() ;
    int getId();

    void setPos(Vector2 np);
    void setVelocity(Vector2 nv);
    void setRadius(float nr);
    void setId(int ni);

    void update(float dt);

    void draw();
};

#endif