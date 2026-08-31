#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <array>

#include "constants.h"
#include "aux_functions.h"
#include "spaceship.h"
#include "asteroid.h"
#include "bullet.h"

class Game
{
protected:
    Spaceship ship;
    std::array<Asteroid, MAX_ASTEROID_NUMBER> asteroids;
    std::array<Bullet, MAX_BULLET_NUMBER> bullets;
    size_t n_asteroids;
    size_t n_bullets;
    unsigned int wave;
    double last_bullet_time;
    double last_gameover_time;
    double last_ship_grace_time;
    unsigned int score;
    float score_mult;
    unsigned int lives;
    bool running;

private:
    void spawnAsteroid(Vector2 pos, int id, float size, unsigned int value);
    void removeAsteroid(int id);
    void splitAsteroid(Asteroid& asteroid);
    
    void generateNextWave(unsigned int wave_asteroids);

    void checkCollisionBulletsEdge();
    void checkCollisionBulletsAsteroid();
    void checkCollisionShipAsteroid();

    bool bulletCooldown();
    bool gameOverCooldown();

    void shootBullet();

    void gameOver();
    void restartGame();
    void resetShip();

    void checkInputStart();

public:
    Game();

    void inputCheck(float dt);

    void update(float dt);

    void checkWave();
    void checkShipGracePeriod();
    void checkCollisions();

    void draw();
};

#endif