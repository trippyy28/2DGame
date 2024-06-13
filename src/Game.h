#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <SFML/Graphics.hpp>

struct PlayerConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
    float S;
};

struct EnemyConfig
{
    int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI;
    float SMIN, SMAX;
};

struct BulletConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
    float S;
};

class Game
{
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player = nullptr;
    std::shared_ptr<Entity> m_enemy = nullptr;

    void init(const std::string &config); // Initialize the game
    void setPaused(bool paused);          // Set the game paused state

    void sMovement();     // Movement system
    void sUserInput();    // User input system
    void sLifespan();     // Lifespan system
    void sRender();       // Render system
    void sEnemySpawner(); // Enemy spawner system
    void sCollision();    // Collision system

    void spawnPlayer();                                                     // Spawn the player
    void spawnEnemy();                                                      // Spawn an enemy
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);                 // Spawn small enemies
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos); // Spawn a bullet
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);                // Spawn a special weapon

public:
    Game(const std::string &config); // Constructor

    void run(); // Run the game
};
