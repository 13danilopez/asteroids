#include "spaceship.h"

// CONSTRUCTOR
Spaceship::Spaceship(Vector2 pos)
    :   pos{pos},
        velocity{(Vector2) {0.0f, 0.0f}},
        angle{0.0f},            // Angle: 0..2pi => 1 vuelta
        vertices
        {
            (Vector2) { pos.x + std::sin(angle) * SHIP_SIZE,
                        pos.y - std::cos(angle) * SHIP_SIZE },
            (Vector2) { pos.x + std::sin(angle + 2.5f) * SHIP_SIZE,
                        pos.y - std::cos(angle + 2.5f) * SHIP_SIZE },
            (Vector2) { pos.x + std::sin(angle - 2.5f) * SHIP_SIZE,
                        pos.y - std::cos(angle - 2.5f) * SHIP_SIZE }
        }
{}

// GETTERS
Vector2 Spaceship::getPos() { return pos; }
Vector2 Spaceship::getVelocity() { return velocity; }
float Spaceship::getAngle() { return angle; }
std::array<Vector2,3> Spaceship::getVertices() { return vertices; }
Vector2 Spaceship::getNose() { return vertices[0]; }

// SETTERS
void Spaceship::setPos(Vector2 np) { pos = np; }
void Spaceship::setVelocity(Vector2 nv) { velocity = nv; }
void Spaceship::setVelocity_x(float nv_x) { velocity.x = nv_x; }
void Spaceship::setVelocity_y(float nv_y) { velocity.y = nv_y; }
void Spaceship::setAngle(float na) { angle = na; }

// PRIVATE METHODS
void Spaceship::limitShipVelocity()
{
    if (velocity.x > +MAX_SHIP_SPEED) velocity.x = +MAX_SHIP_SPEED;
    if (velocity.x < -MAX_SHIP_SPEED) velocity.x = -MAX_SHIP_SPEED;
    if (velocity.y > +MAX_SHIP_SPEED) velocity.y = +MAX_SHIP_SPEED;
    if (velocity.y < -MAX_SHIP_SPEED) velocity.y = -MAX_SHIP_SPEED;
}

void Spaceship::wrapShip()
{
    if (pos.x < 0.0f) 
    { 
        pos.x += (float) WINDOW_WIDTH;
        vertices[0].x += (float) WINDOW_WIDTH;
        vertices[1].x += (float) WINDOW_WIDTH;
        vertices[2].x += (float) WINDOW_WIDTH;
    }
    if (pos.x >= WINDOW_WIDTH) 
    { 
        pos.x -= (float) WINDOW_WIDTH;  
        vertices[0].x -= (float) WINDOW_WIDTH;
        vertices[1].x -= (float) WINDOW_WIDTH;
        vertices[2].x -= (float) WINDOW_WIDTH;
    }
    if (pos.y < 0.0f) 
    { 
        pos.y += (float) WINDOW_HEIGHT; 
        vertices[0].y += (float) WINDOW_WIDTH;
        vertices[1].y += (float) WINDOW_WIDTH;
        vertices[2].y += (float) WINDOW_WIDTH;
    }
    if (pos.y >= WINDOW_HEIGHT) 
    { 
        pos.y -= (float) WINDOW_HEIGHT; 
        vertices[0].y += (float) WINDOW_WIDTH;
        vertices[1].y += (float) WINDOW_WIDTH;
        vertices[2].y += (float) WINDOW_WIDTH;
    }
}

// PUBLIC METHODS
void Spaceship::rotateLeft(float dt)
{
    angle -= SHIP_STEER_POWER * dt;
}

void Spaceship::rotateRight(float dt)
{
    angle += SHIP_STEER_POWER * dt;
}

void Spaceship::thrustForward(float dt)
{
    velocity.x += std::sin(angle) * SHIP_THRUST_POWER * dt;
    velocity.y += std::cos(angle) * SHIP_THRUST_POWER * dt;
    limitShipVelocity();
}

// UPDATE METHOD
void Spaceship::update(float dt)
{
    // Update center position
    pos.x += velocity.x * dt;
    pos.y -= velocity.y * dt;
    // Update vertices
    vertices[0].x = pos.x + std::sin(angle) * SHIP_SIZE;
    vertices[0].y = pos.y - std::cos(angle) * SHIP_SIZE;
    vertices[1].x = pos.x + std::sin(angle + 2.5f) * SHIP_SIZE;
    vertices[1].y = pos.y - std::cos(angle + 2.5f) * SHIP_SIZE;
    vertices[2].x = pos.x + std::sin(angle - 2.5f) * SHIP_SIZE;
    vertices[2].y = pos.y - std::cos(angle - 2.5f) * SHIP_SIZE;
    // Wrap ship altogether (pos & vertices)
    wrapShip();
}

// DRAW METHOD
void Spaceship::draw()
{
    DrawTriangleLines(vertices[0], vertices[1], vertices[2], WHITE);

    // Object Debug Info
     //DrawCircleV(pos, 2.0f, RED);
     //DrawCircleV(vertices[0], 2.0f, BLUE);
     //DrawCircleV(vertices[1], 2.0f, BLUE);
     //DrawCircleV(vertices[2], 2.0f, BLUE);
     //DrawText(TextFormat("ship angle: %f", angle), 20, 20, 20, WHITE);
     //DrawText(TextFormat("ship velocity: (%f,%f)", velocity.x, velocity.y), 20, 60, 20, WHITE);
}