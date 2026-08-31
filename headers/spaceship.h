#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"
#include <array>

#include "constants.h"
#include "aux_functions.h"

class Spaceship
{
protected:
    Vector2 pos; // Represents the center of the triangle
    Vector2 velocity;
    float angle;
    std::array<Vector2,3> vertices;
    bool invulnerable;
    Color color;
    double last_blink_time;

private:
    void limitShipVelocity();

    void wrapShip();

public:
    Spaceship(Vector2 pos);

    Vector2 getPos();
    Vector2 getVelocity();
    float getAngle();
    std::array<Vector2,3> getVertices();
    Vector2 getNose();

    void setPos(Vector2 np);
    void setVelocity(Vector2 nv);
    void setVelocity_x(float nv_x);
    void setVelocity_y(float nv_y);
    void setAngle(float na);
    void setInvulnerable(bool ns);

    bool isInvulnerable();

    void blink();

    void rotateLeft(float dt);
    void rotateRight(float dt);

    void thrustForward(float dt);

    void update(float dt);

    void draw();
};

#endif