#include "bullet.h"

// CONSTRUCTOTS
Bullet::Bullet()
    :   pos{0.0f, 0.0f},
        velocity{0.0f, 0.0f},
        angle{0.0f}
{}

Bullet::Bullet(Vector2 pos, Vector2 velocity, float angle)
    :   pos{pos}, 
        velocity{velocity}, 
        angle{angle}
{}

// GETTERS
Vector2 Bullet::getPos() { return pos; }

// UPDATE METHOD
void Bullet::update(float dt)
{
    pos.x += velocity.x * dt;
    pos.y -= velocity.y * dt;
}

// DRAW METHOD
void Bullet::draw()
{
    DrawCircleV(pos, BULLET_RADIUS, WHITE);
}