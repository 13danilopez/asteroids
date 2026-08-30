#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include <random>

#include "constants.h"

void wrapCoords(float& x, float& y);

inline bool validAsteroidPos(Vector2 generated_asteroid_pos, Vector2 ship_pos);
    
Vector2 generateRandomPos(Vector2 ship_pos);

Vector2 generateRandomVelocity();

float generateRandomAngle();

#endif