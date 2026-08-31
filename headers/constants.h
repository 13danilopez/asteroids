#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

// window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// ship-related constants
#define SHIP_SIZE 16
#define SHIP_VELOCITY 0.05f
#define SHIP_THRUST_POWER 100.0f
#define SHIP_STEER_POWER 3.0f
#define SHIP_GRACE_PERIOD 3.0f
#define SHIP_BLINK_DELAY 5.0f
#define MAX_SHIP_SPEED 200.0f

// asteroid-related constants
#define ASTEROID_MIN_VELOCITY 20.0f
#define ASTEROID_MAX_VELOCITY 70.0f
#define ASTEROID_SPAWN_MARGIN 40
#define ASTEROID_SAFE_SPAWN_RADIUS 300
#define MAX_ASTEROID_NUMBER 128
enum ASTEROID_SIZE { SMALL = 0, MEDIUM = 1, LARGE = 2 };
const std::array<float, 3> ASTEROID_RADIUS { 15.0f, 30.0f, 60.0f };
const std::array<unsigned int, 3> ASTEROID_VALUE { 10, 25, 50 };

// bullet-related constants
#define BULLET_RADIUS 2.0f
#define BULLET_SPEED 400.0f
#define BULLET_COOLDOWN 0.25f
#define MAX_BULLET_NUMBER 32

// wave-related constants
#define WAVE_ASTEROID_MULTIPLIER 3
#define WAVE_SCORE_MULTIPLIER 1.2f
#define WAVE_CLEAR_BONUS 100

// text-related constants
#define WINDOW_TEXT_MARGIN 20
#define TEXT_MARGIN 30
#define FONT_SIZE 20

// gameover-system-related constants
#define GAMEOVER_FONT_SIZE 50
#define GAMEOVER_COOLDOWN 1.0f

// lives-system-related constants
#define MAX_LIVES 3

#endif