#include "game.h"

// CONSTRUCTOR
Game::Game()
    :   ship((Vector2){WINDOW_WIDTH/2,WINDOW_HEIGHT/2}), 
        asteroids{}, 
        bullets{}, 
        n_asteroids{0}, 
        n_bullets{0}, 
        wave{0}, 
        score{0}, 
        lives{MAX_LIVES}, 
        score_mult{1.0f}, 
        bullet_cooldown_timer{0.0f}, 
        gameover_timer{0.0f}, 
        ship_respawn_timer{0.0f}, 
        running{true}
{}

// PRIVATE METHODS
void Game::spawnAsteroid(Vector2 pos, int id, float radius, unsigned int value)
{
    Vector2 velocity = generateRandomVelocity();
    float angle = generateRandomAngle();
    asteroids[id] = (Asteroid) {pos, velocity, angle, radius, value, id};
    n_asteroids++;
}
    
void Game::generateNextWave(unsigned int wave_asteroids)
{
    for (size_t i = 0; i < wave_asteroids; ++i)
    {
        Vector2 pos = generateRandomPos(ship.getPos());
        spawnAsteroid(pos, i, ASTEROID_RADIUS[LARGE], ASTEROID_VALUE[LARGE]);
    }
}

void Game::removeAsteroid(int id)
{
    asteroids[id] = asteroids[n_asteroids-1];
    asteroids[id].setId(id);
    n_asteroids--;
}

void Game::splitAsteroid(Asteroid& asteroid)
{
    Vector2 pos = asteroid.getPos();
    float radius = asteroid.getRadius();
    removeAsteroid(asteroid.getId());

    if (radius == ASTEROID_RADIUS[LARGE])
    {
        spawnAsteroid(pos, n_asteroids, ASTEROID_RADIUS[MEDIUM], ASTEROID_VALUE[MEDIUM]);
        spawnAsteroid(pos, n_asteroids, ASTEROID_RADIUS[MEDIUM], ASTEROID_VALUE[MEDIUM]);
    }
    else if (radius == ASTEROID_RADIUS[MEDIUM])
    {
        spawnAsteroid(pos, n_asteroids, ASTEROID_RADIUS[SMALL], ASTEROID_VALUE[SMALL]);
        spawnAsteroid(pos, n_asteroids, ASTEROID_RADIUS[SMALL], ASTEROID_VALUE[SMALL]);
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
    gameover_timer = GAMEOVER_COOLDOWN;

    running = false;
    resetShip();
}

void Game::shootBullet()
{
    bullet_cooldown_timer = BULLET_COOLDOWN;

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

void Game::restartGame()
{
    n_asteroids = 0;
    n_bullets = 0;
    wave = 0;
    score = 0;
    score_mult = 1;
    lives = MAX_LIVES;
    running = true;
}

void Game::checkInputStart()
{
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE))
    {
        restartGame();
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
                score += asteroid.getValue() * score_mult;
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
        // check triangle-circle collision (all 3 lines of the triangle)
        if (CheckCollisionCircleLine(asteroid.getPos(), asteroid.getRadius(), ship.getVertices()[0], ship.getVertices()[1]) ||
            CheckCollisionCircleLine(asteroid.getPos(), asteroid.getRadius(), ship.getVertices()[1], ship.getVertices()[2]) ||
            CheckCollisionCircleLine(asteroid.getPos(), asteroid.getRadius(), ship.getVertices()[2], ship.getVertices()[0]))
        {
            lives--;
            if (lives > 0) 
            { 
                resetShip();
                ship.startInvulnerability();
            }
            else 
            {
                gameOver();
            }
        }
    }
}

// PUBLIC METHODS
// INPUT CHECK METHOD
void Game::inputCheck(float dt)
{
    if (!running && gameover_timer <= 0.0f) { checkInputStart(); }

    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) { ship.rotateLeft(dt); }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) { ship.rotateRight(dt); }
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) { ship.thrustForward(dt); }
    if (IsKeyDown(KEY_SPACE))
    {
        if (n_bullets < MAX_BULLET_NUMBER && bullet_cooldown_timer <= 0.0f)
        {
            shootBullet();
        }
    }
}

// OBJECTS STATE UPDATE METHOD (can stop updating while !running)
void Game::updateObjects(float dt)
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

// TIMERS UPDATE METHOD (keep updating gameover_timer while !running)
void Game::updateTimers(float dt)
{
    if (bullet_cooldown_timer > 0.0f)  { bullet_cooldown_timer -= dt; }
    if (gameover_timer > 0.0f)         { gameover_timer -= dt; }
}

// WAVE STATUS CHECK METHOD
void Game::checkWave()
{
    if (!running) { return; }
    if (n_asteroids == 0)
    {
        wave++;
        if (wave > 1) 
        { 
            score += WAVE_CLEAR_BONUS * score_mult;
            score_mult += WAVE_SCORE_MULTIPLIER;
        }
        if (lives < MAX_LIVES)
        {
            lives++;
        }
        unsigned int wave_asteroids = (unsigned int) (std::sqrt(wave) * WAVE_ASTEROID_MULTIPLIER);
        generateNextWave(wave_asteroids);
    }
}

// COLLISION CHECK METHOD (GENERAL)
void Game::checkCollisions()
{
    if (!running) { return; }
    checkCollisionBulletsEdge();
    checkCollisionBulletsAsteroid();
    if (!ship.isInvulnerable()) checkCollisionShipAsteroid();
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
    // Wave, Score and Lives
    DrawText(TextFormat("wave: %u", wave), WINDOW_TEXT_MARGIN, WINDOW_TEXT_MARGIN, FONT_SIZE, WHITE);
    DrawText(TextFormat("score: %u", score), WINDOW_TEXT_MARGIN, WINDOW_TEXT_MARGIN + TEXT_MARGIN, FONT_SIZE, WHITE);
    DrawText(TextFormat("lives: %u", lives), WINDOW_TEXT_MARGIN, WINDOW_TEXT_MARGIN + 2*TEXT_MARGIN, FONT_SIZE, WHITE);

    if (!running) 
    { 
        int gameover_text_width = MeasureText("GAME OVER", GAMEOVER_FONT_SIZE);
        DrawText(TextFormat("GAME OVER"), WINDOW_WIDTH/2 - gameover_text_width/2, WINDOW_HEIGHT/2 - GAMEOVER_FONT_SIZE/2 - 40, GAMEOVER_FONT_SIZE, RED);
        if (gameover_timer <= 0.0f)
        {
            int press_key_text_width = MeasureText("[press key to start]", FONT_SIZE);
            DrawText(TextFormat("[press key to start]"), WINDOW_WIDTH/2 - press_key_text_width/2, WINDOW_HEIGHT/2 - FONT_SIZE/2, FONT_SIZE, WHITE);
        }
    }
    EndDrawing();
}