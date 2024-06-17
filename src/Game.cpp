#include "Game.h"

Game::Game(const std::string &config)
{
    init(config);
}

void Game::init(const std::string &path)
{
    std::ifstream configFile(path);
    if (!configFile.is_open())
    {
        std::cerr << "Failed to open config file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        std::istringstream iss(line);
        std::string key;
        if (!(iss >> key))
        {
            continue; // Skip empty lines
        }

        if (key == "Window")
        {
            int width, height, frameRate, fullscreen;
            if (iss >> width >> height >> frameRate >> fullscreen)
            {
                m_window.create(sf::VideoMode(width, height), "SFML Game");
                m_window.setFramerateLimit(frameRate);
                // Handle fullscreen if needed
            }
        }
        if (key == "Player")
        {
            iss >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V >> m_playerConfig.S;
        }

        if (key == "Bullet")
        {
            iss >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L >> m_bulletConfig.S;
        }

        // Load the font from the config file path

        if (!m_font.loadFromFile("/users/trippyy28/Desktop/2DGame/src/font.ttf"))
        {
            std::cerr << "Failed to load font: " << std::endl;
        }

        m_text.setFont(m_font);
        m_text.setCharacterSize(20);
        m_text.setFillColor(sf::Color(200, 200, 100));
    }

    configFile.close();
    spawnPlayer(); // Continue parsing other keys as needed
}

void Game::run()
{
    while (m_running)
    {
        m_entities.update();
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();

        m_currentFrame++;
    }
}

void Game::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_running = false;
            }
            if (event.key.code == sf::Keyboard::W)
            {
                m_player->cInput->up = true;
            }
            if (event.key.code == sf::Keyboard::A)
            {
                m_player->cInput->left = true;
            }
            if (event.key.code == sf::Keyboard::S)
            {
                m_player->cInput->down = true;
            }
            if (event.key.code == sf::Keyboard::D)
            {
                m_player->cInput->right = true;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::W)
            {
                m_player->cInput->up = false;
                if (m_player->cTransform->pos.y < 35)
                    m_player->cTransform->pos.y = 35;
            }
            if (event.key.code == sf::Keyboard::A)
            {
                m_player->cInput->left = false;
                if (m_player->cTransform->pos.x < 35)
                    m_player->cTransform->pos.x = 35;
            }
            if (event.key.code == sf::Keyboard::S)
            {
                m_player->cInput->down = false;
                if (m_player->cTransform->pos.y > m_window.getSize().y - 35)
                    m_player->cTransform->pos.y = m_window.getSize().y - 35;
            }
            if (event.key.code == sf::Keyboard::D)
            {
                m_player->cInput->right = false;
                if (m_player->cTransform->pos.x > m_window.getSize().x - 35)
                    m_player->cTransform->pos.x = m_window.getSize().x - 35;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            m_player->cInput->shot = true;
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            spawnBullet(m_player, Vec2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
            std::cout << "Mouse position: " << mousePos.x << ", " << mousePos.y << std::endl;
            std::cout << m_entities.getEntities("bullet").size() << std::endl;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            m_player->cInput->shot = false;
        }
    }

    // Update player position based on input
    if (m_player && m_player->cInput)
    {
        if (m_player->cInput->up)
        {
            m_player->cTransform->pos.y -= m_playerConfig.S;
            if (m_player->cTransform->pos.y < 35)
                m_player->cTransform->pos.y = 35;
        }
        if (m_player->cInput->down)
        {
            m_player->cTransform->pos.y += m_playerConfig.S;
            if (m_player->cTransform->pos.y > m_window.getSize().y - 35)
                m_player->cTransform->pos.y = m_window.getSize().y - 35;
        }
        if (m_player->cInput->left)
        {
            m_player->cTransform->pos.x -= m_playerConfig.S;
            if (m_player->cTransform->pos.x < 35)
                m_player->cTransform->pos.x = 35;
        }
        if (m_player->cInput->right)
        {

            m_player->cTransform->pos.x += m_playerConfig.S;
            if (m_player->cTransform->pos.x > m_window.getSize().x - 35)
                m_player->cTransform->pos.x = m_window.getSize().x - 35;
        }
        if (m_player->cInput->shot)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            spawnBullet(m_player, Vec2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        }
    }
}

void Game::spawnPlayer()
{
    auto entity = m_entities.addEntity("player");

    if (entity)
    {
        entity->cTransform = std::make_shared<CTransform>(Vec2(200, 200), Vec2(0.0f, 0.0f), 0.0f);
        entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 0, 0), sf::Color(255, 0, 0), 4.0f);
        entity->cInput = std::make_shared<CInput>();
        m_player = entity;
    }
    else
    {
        std::cerr << "Failed to add player entity!" << std::endl;
    }
}

void Game::sCollision()
{
    // TODO: Implement collision detection logic here
    // Example:
    // - Check for collisions between player and enemies
    // - Check for collisions between bullets and enemies
    // - Handle collisions appropriately
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos)
{
    // Create a new bullet entity
    auto bullet = m_entities.addEntity("bullet");

    if (bullet)
    {
        Vec2 direction = mousePos - entity->cTransform->pos;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0)
        {
            direction.x /= magnitude;
            direction.y /= magnitude;
        }
        bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, direction * m_bulletConfig.S, 0.0f);
        bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, 10, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
        bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
    }
    // std::cout << "Bullet spawned!" << std::endl;
    // std::cout << mousePos.x << " " << mousePos.y << std::endl;
    // std::cout << bullet->cTransform->pos.x << " " << bullet->cTransform->pos.y << std::endl;
    // /// is shot = true
    // std::cout << m_player->cInput->shot << "shot" << std::endl;
}

void Game::spawnEnemy()
{
    // TODO: Implement enemy spawning logic
    auto entity = m_entities.addEntity("enemy");

    if (entity)
    {
        float ex = rand() % m_window.getSize().x;
        float ey = rand() % m_window.getSize().y;

        entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);
        entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
        m_lastEnemySpawnTime = m_currentFrame;
    }
    else
    {
        std::cerr << "Failed to add enemy entity!" << std::endl;
    }
}

void Game::sEnemySpawner()
{
    // Implement enemy spawning logic here
    if ((m_currentFrame - m_lastEnemySpawnTime) > 60) // Spawn enemy every 60 frames
    {
        spawnEnemy();
        m_lastEnemySpawnTime = m_currentFrame;
    }
}

void Game::sMovement()
{
    // Update player position based on input
    if (m_player && m_player->cInput)
    {
        if (m_player->cInput->up)
        {
            m_player->cTransform->pos.y -= m_playerConfig.S;
        }
        if (m_player->cInput->down)
        {
            m_player->cTransform->pos.y += m_playerConfig.S;
        }
        if (m_player->cInput->left)
        {
            m_player->cTransform->pos.x -= m_playerConfig.S;
        }
        if (m_player->cInput->right)
        {
            m_player->cTransform->pos.x += m_playerConfig.S;
        }
    }

    // Update positions of all entities based on their velocities
    for (auto &e : m_entities.getEntities())
    {
        if (e->cTransform)
        {
            e->cTransform->pos += e->cTransform->vel;
        }
        // print the velocity of the enemy
        std::cout << e->cTransform->vel.x << "velooo " << e->cTransform->vel.y << std::endl;
    }
}

void Game::sRender()
{
    m_window.clear();

    // Draw all entities
    for (auto &e : m_entities.getEntities("enemy"))
    {
        if (e && e->cShape && e->cTransform)
        {
            e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
            e->cTransform->angle += 0.1f;
            e->cShape->circle.setRotation(e->cTransform->angle);
            m_window.draw(e->cShape->circle);
        }
    }

    // Draw the player entity
    if (m_player && m_player->cShape && m_player->cTransform)
    {
        m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);
        m_window.draw(m_player->cShape->circle);
    }

    // Draw the bullet
    // Draw all bullets
    for (auto &e : m_entities.getEntities("bullet"))
    {
        if (e && e->cShape && e->cTransform)
        {
            e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
            m_window.draw(e->cShape->circle);
        }
    }

    // Draw the score or other text if needed
    m_window.draw(m_text);

    m_window.display();
}

// Display configuration data
// std::ostringstream oss;
// oss << "Window: 800x600\n"
//     << "Player: SR=32, CR=32, V=8, S=5\n"
//     << "Enemy: SR=32, CR=32, VMIN=2, VMAX=3\n"
//     << "Bullet: SR=10, CR=10, V=20\n";

// m_text.setString(oss.str());
// m_text.setPosition(10, 10); // Adjust position as needed
