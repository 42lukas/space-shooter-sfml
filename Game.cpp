#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

// const um einfacher Änderungen im ganzen code vornehmen zu können
const int MAX_ENEMIES = 12;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 1000;

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Shooter"), playerLives(50) {
    player.shape.setPosition(WINDOW_WIDTH * 1/2, WINDOW_HEIGHT * 5/6);
    spawnClock.restart();
    std::srand(std::time(nullptr));

    if (!font.loadFromFile("assets/varsity_regular.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }
    playerLivesText.setFont(font);
    playerLivesText.setCharacterSize(24);
    playerLivesText.setFillColor(sf::Color::White);
    playerLivesText.setPosition(10, 10);
    playerLivesText.setString("Leben: " + std::to_string(playerLives));

    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "Fehler beim Laden des Hintergrundbildes!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x,
        static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y
    );
}

// main-gameloop
void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents(clock);
        update();
        render();
    }
}

// Verarbeitet Benutzer-Eingaben
void Game::processEvents(sf::Clock& clock) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    player.handleInput(bullets, clock);
}

// updated alle Game Objects
void Game::update() {
    player.update();
    for (auto& enemy : enemies) enemy.update(bullets);
    for (auto& bullet : bullets) bullet.update();

    // Entfernt Kugeln, die außerhalb des Spielfelds sind
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
        return b.shape.getPosition().y < 0 || b.shape.getPosition().y > WINDOW_HEIGHT;
        }), bullets.end());

    // Entfernt Gegner, die außerhalb des Spielfelds sind
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy& e) {
        if (e.shape.getPosition().y > WINDOW_HEIGHT) {
            playerLives--;
            if (playerLives <= 0) {
                std::cout << "Game Over!" << std::endl;
                window.close();
            }
            return true;
        }
        return false;
        }), enemies.end());

    // spawned Gegner jede Sekunde
    if (spawnClock.getElapsedTime().asSeconds() > 1 && enemies.size() < MAX_ENEMIES) {
        spawnEnemies();
        spawnClock.restart();
    }

    checkCollisions();
    playerLivesText.setString("Leben: " + std::to_string(playerLives));
}

// spawned neue Gegner random am oberen Bildschirmrand
void Game::spawnEnemies() {
    float x = static_cast<float>(std::rand() % (WINDOW_WIDTH - 50));
    int enemyType = std::rand() % 2; // 0 = Normaler Gegner, 1 = Tank
    if (enemyType == 0) {
        enemies.emplace_back(x, 0);
    }
    else {
        enemies.emplace_back(Enemy(x, 0, 3, 0.02f, 1500)); // Tank: 3 Leben, langsamer, schießt schneller
    }
}

// rendert das gesamte Spiel mit allen Gegnern, dem Spieler, usw.
void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    player.draw(window);
    for (auto& enemy : enemies) enemy.draw(window);
    for (auto& bullet : bullets) bullet.draw(window);
    window.draw(playerLivesText);
    window.display();
}

void Game::checkCollisions() {
    // checkt ob Player Bullets mit Gegnern colliden
    for (auto it = enemies.begin(); it != enemies.end();) {
        bool enemyHit = false;
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            if (bulletIt->isPlayerBullet && it->isHit(*bulletIt)) {
                bulletIt = bullets.erase(bulletIt);
                enemyHit = true;
                it->takeDamage();
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

    // checkt ob Enemy Bullets mit dem Player colliden
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

    // Note: aktiv gegen friendly fire entschieden, da es meiner Meinung nach mehr Sinn ergibt
}
