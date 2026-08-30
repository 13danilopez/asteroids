#include "game.h"

// CONSTRUCTOR
Game::Game()
    :   ship((Vector2){WINDOW_WIDTH/2,WINDOW_HEIGHT/2}), 
        asteroids{},  
        bullets{}, 
        n_asteroids{0},
        n_bullets{0}, 
        wave{0}, 
        last_bullet_time{0},
        last_gameover_time{0},
        running{true}
{}

// PRIVATE METHODS
void Game::spawnAsteroid(Vector2 pos, int id, enum ASTEROID_SIZE size)
{
    Vector2 velocity = generateRandomVelocity();
    float angle = generateRandomAngle();
    asteroids[id] = (Asteroid) {pos, velocity, angle, (float) size, id};
    n_asteroids++;
}
    
void Game::generateNextWave(unsigned int wave_asteroids)
{
    for (size_t i = 0; i < wave_asteroids; ++i)
    {
        Vector2 pos = generateRandomPos(ship.getPos());
        spawnAsteroid(pos, i, LARGE);
    }
}

void Game::splitAsteroid(Asteroid& asteroid)
{
    Vector2 pos = asteroid.getPos();
    float radius = asteroid.getRadius();
    int id = asteroid.getId();

    asteroids[id] = asteroids[n_asteroids-1];
    asteroids[id].setId(id);
    n_asteroids--;

    if (radius == LARGE)
    {
        spawnAsteroid(pos, n_asteroids, MEDIUM);
        spawnAsteroid(pos, n_asteroids, MEDIUM);
    }
    else if (radius == MEDIUM)
    {
        spawnAsteroid(pos, n_asteroids, SMALL);
        spawnAsteroid(pos, n_asteroids, SMALL);
    }
}

void Game::resetShip()
{
    ship.setPos((Vector2) {WINDOW_WIDTH/2, WINDOW_HEIGHT/2});
    ship.setVelocity((Vector2) {0.0f, 0.0f});
    ship.setAngle(0.0f);
}

void Game::gameOver()
{
    running = false;
    last_gameover_time = GetTime();
    resetShip();
}

bool Game::bulletCooldown()
{
    double current_time = GetTime();
    if (current_time - last_bullet_time >= BULLET_COOLDOWN)
    {
        last_bullet_time = current_time;
        return true;
    }
    return false;
}

bool Game::gameOverCooldown()
{
    double current_time = GetTime();
    if (current_time - last_gameover_time >= GAMEOVER_COOLDOWN)
    {
        return true;
    }
    return false;
}

void Game::shootBullet()
{
    Vector2 ship_nose = ship.getNose();
    Vector2 ship_velocity = {
        std::sin(ship.getAngle()) * BULLET_SPEED,
        std::cos(ship.getAngle()) * BULLET_SPEED
    };
    float ship_angle = ship.getAngle();

    Bullet new_bullet {ship_nose, ship_velocity, ship_angle};
    bullets[n_bullets] = new_bullet;
    n_bullets++;
}

void Game::resetGame()
{
    n_asteroids = 0;
    n_bullets = 0;
    wave = 0;
    running = true;
}

void Game::checkInputStart()
{
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE))
    {
        resetGame();
    }
}

// COLLISION CHECK METHODS
void Game::checkCollisionBulletsAsteroid()
{
    for (size_t i = 0; i < n_bullets; ++i)
    {
        for (size_t j = 0; j < n_asteroids; ++j)
        {
            Bullet bullet = bullets[i];
            Asteroid& asteroid = asteroids[j];
            if (CheckCollisionCircles(bullet.getPos(), BULLET_RADIUS, asteroid.getPos(), asteroid.getRadius()))
            {
                bullets[i] = bullets[n_bullets-1];
                n_bullets--;
                splitAsteroid(asteroid);
            }
        }
    }
}

void Game::checkCollisionBulletsEdge()
{
    for (size_t i = 0; i < n_bullets; ++i)
    {
        Vector2 pos = bullets[i].getPos();
        if (pos.x >= WINDOW_WIDTH || pos.x < 0 || pos.y >= WINDOW_HEIGHT || pos.y < 0)
        {
            bullets[i] = bullets[n_bullets-1];
            n_bullets--;
        }
    }
}

void Game::checkCollisionShipAsteroid()
{
    for (size_t i = 0; i < n_asteroids; ++i)
    {
        Asteroid asteroid = asteroids[i];
        // Check triangle-circle collision (all 3 lines of the triangle)
        if (CheckCollisionCircleLine(asteroid.getPos(), asteroid.getRadius(), ship.getVertices()[0], ship.getVertices()[1]) ||
            CheckCollisionCircleLine(asteroid.getPos(), asteroid.getRadius(), ship.getVertices()[1], ship.getVertices()[2]) ||
            CheckCollisionCircleLine(asteroid.getPos(), asteroid.getRadius(), ship.getVertices()[2], ship.getVertices()[0]))
        {
            gameOver();
        }
    }
}

// PUBLIC METHODS
// INPUT CHECK METHOD
void Game::inputCheck(float dt)
{
    if (!running && gameOverCooldown()) { checkInputStart(); }

    if (IsKeyDown(KEY_LEFT))  { ship.rotateLeft(dt); }
    if (IsKeyDown(KEY_RIGHT)) { ship.rotateRight(dt); }
    if (IsKeyDown(KEY_UP))    { ship.thrustForward(dt); }
    if (IsKeyDown(KEY_SPACE))
    {
        if (n_bullets < MAX_BULLET_NUMBER && bulletCooldown())
        {
            shootBullet();
        }
    }
}

// WAVE STATUS CHECK METHOD
void Game::checkWave()
{
    if (!running) { return; }
    if (n_asteroids == 0)
    {
        wave++;
        unsigned int wave_asteroids = (unsigned int) (std::sqrt(wave) * WAVE_MULTIPLIER);
        //bullets.reset(); ???
        generateNextWave(wave_asteroids);
    }
}

// COLLISION CHECK METHOD (GENERAL)
void Game::checkCollisions()
{
    if (!running) { return; }
    checkCollisionBulletsEdge();
    checkCollisionBulletsAsteroid();
    checkCollisionShipAsteroid();
}

// UPDATE METHOD
void Game::update(float dt)
{
    if (!running) { return; }
    // Ship
    ship.update(dt);
    // Asteroids
    for (size_t i = 0; i < n_asteroids; ++i) { asteroids[i].update(dt); }
    // Bullets
    for (size_t i = 0; i < n_bullets; ++i) { bullets[i].update(dt); }
    
    // Object Debug Info
     //std::cout << "n_asteroids: " << n_asteroids << std::endl;
     //std::cout << "n_bullets: " << n_bullets << std::endl;
}

// DRAW METHOD
void Game::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    // Ship
    ship.draw();
    // Asteroids
    for (size_t i = 0; i < n_asteroids; ++i) { asteroids[i].draw(); }
    // Bullets
    for (size_t i = 0; i < n_bullets; ++i) { bullets[i].draw(); }
    // Wave number
    DrawText(TextFormat("wave: %u", wave), WINDOW_TEXT_MARGIN, WINDOW_TEXT_MARGIN, FONT_SIZE, WHITE);
    if (!running) 
    { 
        int gameover_text_width = MeasureText("GAME OVER", GAMEOVER_FONT_SIZE);
        DrawText(TextFormat("GAME OVER"), WINDOW_WIDTH/2 - gameover_text_width/2, WINDOW_HEIGHT/2 - GAMEOVER_FONT_SIZE/2 - 40, GAMEOVER_FONT_SIZE, RED);
        if (gameOverCooldown())
        {
            int press_key_text_width = MeasureText("[press key to start]", FONT_SIZE);
            DrawText(TextFormat("[press key to start]"), WINDOW_WIDTH/2 - press_key_text_width/2, WINDOW_HEIGHT/2 - FONT_SIZE/2, FONT_SIZE, WHITE);
        }
    }
    EndDrawing();
}