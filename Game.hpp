#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    int playerLives;
    sf::Clock spawnClock;
    sf::Font font;
    sf::Text playerLivesText;

    void processEvents(sf::Clock& clock);
    void update();
    void render();
    void spawnEnemies();
    void checkCollisions();
};

#endif
