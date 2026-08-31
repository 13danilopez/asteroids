#include "asteroid.h"

// CONSTRUCTORS
Asteroid::Asteroid()
    :   pos{0.0f, 0.0f},
        velocity{0.0f, 0.0f},
        angle{0.0f},
        radius{0.0f},
        value{0},
        id{-1}
{}

Asteroid::Asteroid(Vector2 pos, Vector2 velocity, float angle, float radius, unsigned int value, int id)
    :   pos{pos},
        velocity(velocity),
        angle{angle},
        radius{radius},
        value{value},
        id{id}
{}

// GETTERS
Vector2 Asteroid::getPos() { return pos; }
Vector2 Asteroid::getVelocity() { return velocity; }
float Asteroid::getRadius() { return radius; }
unsigned int Asteroid::getValue() { return value; }
int Asteroid::getId() { return id; }

// SETTERS
void Asteroid::setPos(Vector2 np) { pos = np; }
void Asteroid::setVelocity(Vector2 nv) { velocity = nv; }
void Asteroid::setRadius(float nr) { radius = nr; }
void Asteroid::setValue(unsigned int nv) { value = nv; }
void Asteroid::setId(int ni) { id = ni; }

// UPDATE METHOD
void Asteroid::update(float dt)
{
    pos.x += velocity.x * std::sin(angle) * dt;
    pos.y -= velocity.y * std::cos(angle) * dt;
    wrapCoords(pos.x, pos.y);
}

// DRAW METHOD
void Asteroid::draw()
{
    DrawCircleLines(pos.x, pos.y, radius, WHITE);

    // Object Debug Info
     //DrawText(TextFormat("asteroid angle: %f", angle), 20, 40, 20, WHITE);
     //DrawText(TextFormat("asteroid velocity: (%f,%f)", velocity.x, velocity.y), 20, 60, 20, WHITE);
     //DrawText(TextFormat("%d", id), pos.x, pos.y, 5, WHITE);
}