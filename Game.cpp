// Game.cpp
#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

const int MAX_ENEMIES = 15;

Game::Game() : window(sf::VideoMode(800, 600), "Space Shooter"), playerLives(5) {
    player.shape.setPosition(400, 550);
    spawnClock.restart();
    std::srand(std::time(nullptr));

    if (!font.loadFromFile("varsity_regular.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }
    playerLivesText.setFont(font);
    playerLivesText.setCharacterSize(24);
    playerLivesText.setFillColor(sf::Color::White);
    playerLivesText.setPosition(10, 10);
    playerLivesText.setString("Leben: " + std::to_string(playerLives));
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents(clock);
        update();
        render();
    }
}

void Game::processEvents(sf::Clock& clock) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    player.handleInput(bullets, clock);
}

void Game::update() {
    player.update();
    for (auto& enemy : enemies) enemy.update(bullets);
    for (auto& bullet : bullets) bullet.update();

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
        return b.shape.getPosition().y < 0 || b.shape.getPosition().y > 600;
        }), bullets.end());

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy& e) {
        if (e.shape.getPosition().y > 600) {
            playerLives--;
            if (playerLives <= 0) {
                std::cout << "Game Over!" << std::endl;
                window.close();
            }
            return true;
        }
        return false;
        }), enemies.end());

    if (spawnClock.getElapsedTime().asSeconds() > 1 && enemies.size() < MAX_ENEMIES) {
        spawnEnemies();
        spawnClock.restart();
    }

    checkCollisions();

    playerLivesText.setString("Leben: " + std::to_string(playerLives));
}

void Game::spawnEnemies() {
    float x = static_cast<float>(std::rand() % 750);
    int enemyType = std::rand() % 3; // 0 = Normal, 1 = Tank
    if (enemyType == 0) {
        enemies.emplace_back(x, 0);
    }
    else if (enemyType == 1) {
        enemies.emplace_back(Enemy(x, 0, 3, 0.02f, 2000)); // Tank: 3 Leben, langsam, langsamer Schuss
    }
}

void Game::render() {
    window.clear();
    player.draw(window);
    for (auto& enemy : enemies) enemy.draw(window);
    for (auto& bullet : bullets) bullet.draw(window);
    window.draw(playerLivesText);
    window.display();
}

void Game::checkCollisions() {
    for (auto it = enemies.begin(); it != enemies.end();) {
        bool enemyHit = false;
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            if (bulletIt->isPlayerBullet && it->isHit(*bulletIt)) {
                bulletIt = bullets.erase(bulletIt);
                enemyHit = true;
                it->takeDamage(); // Tanks haben mehrere Leben
                if (it->isDead()) {
                    it = enemies.erase(it);
                }
                break;
            }
            else {
                ++bulletIt;
            }
        }
        if (!enemyHit) {
            ++it;
        }
    }

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        if (!bulletIt->isPlayerBullet && player.shape.getGlobalBounds().intersects(bulletIt->shape.getGlobalBounds())) {
            bulletIt = bullets.erase(bulletIt);
            playerLives--;
            if (playerLives <= 0) {
                std::cout << "Game Over!" << std::endl;
                window.close();
            }
        }
        else {
            ++bulletIt;
        }
    }

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        if (!bulletIt->isPlayerBullet) {
            bool hitEnemy = false;
            for (auto it = enemies.begin(); it != enemies.end(); ++it) {
                if (it->isHit(*bulletIt)) {
                    hitEnemy = true;
                    break;
                }
            }
            if (hitEnemy) {
                bulletIt = bullets.erase(bulletIt);
            }
            else {
                ++bulletIt;
            }
        }
        else {
            ++bulletIt;
        }
    }
}
