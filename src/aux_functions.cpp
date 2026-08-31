#include "aux_functions.h"

void wrapCoords(float& x, float& y)
{
    float nx = x;
    float ny = y;
    if (x < 0.0f)           { nx = x + (float) WINDOW_WIDTH;  }
    if (x >= WINDOW_WIDTH)  { nx = x - (float) WINDOW_WIDTH;  }
    if (y < 0.0f)           { ny = y + (float) WINDOW_HEIGHT; }
    if (y >= WINDOW_HEIGHT) { ny = y - (float) WINDOW_HEIGHT; }
    x = nx;
    y = ny;
}

inline bool validAsteroidPos(Vector2 generated_asteroid_pos, Vector2 ship_pos)
{
    return Vector2Distance(generated_asteroid_pos, ship_pos) > ASTEROID_SAFE_SPAWN_RADIUS;
}
    
Vector2 generateRandomPos(Vector2 ship_pos)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist_x(ASTEROID_SPAWN_MARGIN, WINDOW_WIDTH - ASTEROID_SPAWN_MARGIN); // distribution in range [n, m]
    std::uniform_real_distribution<float> dist_y(ASTEROID_SPAWN_MARGIN, WINDOW_HEIGHT - ASTEROID_SPAWN_MARGIN); // distribution in range [n, m]

    Vector2 generated_asteroid_pos;
    do {
        generated_asteroid_pos = { dist_x(rng), dist_y(rng) };
    } while (!validAsteroidPos(generated_asteroid_pos, ship_pos));

    return generated_asteroid_pos;
}

Vector2 generateRandomVelocity()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY);
    std::uniform_int_distribution<int> dist_sign(-1,1);

    int x_sign = (dist_sign(rng) >= 0) ? 1 : -1;
    int y_sign = (dist_sign(rng) >= 0) ? 1 : -1;

    Vector2 generated_velocity { x_sign*dist(rng), y_sign*dist(rng) };

    return generated_velocity;
}

float generateRandomAngle()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0, 2*PI);

    float generated_angle = dist(rng);

    return generated_angle;
}