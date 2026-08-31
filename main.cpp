#include "raylib.h"
#include "raymath.h"
#include <random>
#include <cmath>
#include <iostream>
#include <array>

#include "constants.h"
#include "aux_functions.h"
#include "spaceship.h"
#include "asteroid.h"
#include "bullet.h"
#include "game.h"


int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "asteroids");
    SetTargetFPS(60);
    HideCursor();

    Game game;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        /*
         * player inputs modify the ships ANGLE and VELOCITY. POSITION and VERTICES 
         *  are just updated on its own every frame through the .update() method
         */
        // 1- EVENT HANDLING (READ INPUT)
        game.inputCheck(dt);
        // 2- UPDATE GAMESTATE
        game.updateObjects(dt);
        game.updateTimers(dt);
        // 3- STATE CHECKS
        game.checkWave();
        game.checkCollisions();
        // 4- DRAW OBJECTS
        game.draw();
    }

    return 0;
}