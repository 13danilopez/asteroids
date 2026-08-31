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
    unsigned int score;
    unsigned int lives;
    float score_mult;
    float bullet_cooldown_timer;
    float gameover_timer;
    float ship_respawn_timer;
    bool running;

private:
    void spawnAsteroid(Vector2 pos, int id, float size, unsigned int value);
    void removeAsteroid(int id);
    void splitAsteroid(Asteroid& asteroid);
    
    void generateNextWave(unsigned int wave_asteroids);

    void checkCollisionBulletsEdge();
    void checkCollisionBulletsAsteroid();
    void checkCollisionShipAsteroid();

    void shootBullet();

    void gameOver();
    void restartGame();
    void resetShip();

    void checkInputStart();

public:
    Game();

    void init();

    void inputCheck(float dt);

    void updateObjects(float dt);
    void updateTimers(float dt);

    void checkWave();
    void checkShipGracePeriod();
    void checkCollisions();

    void draw();
};

#endif