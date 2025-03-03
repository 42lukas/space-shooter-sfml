// Enemy.cpp
#include "Enemy.hpp"
#include <cstdlib>

Enemy::Enemy(float x, float y, int health, float speed, int shootInterval)
    : health(health), speed(speed), shootInterval(shootInterval) {
    shape.setRadius(20);
    shape.setFillColor(health > 1 ? sf::Color::Blue : sf::Color::Red); // Tanks sind Blau, normale Gegner Rot
    shape.setPosition(x, y);
    shootClock.restart();
    moveClock.restart();
    moveDirection = (std::rand() % 2 == 0) ? -0.05f : 0.05f; // Zufällige Bewegungsrichtung
}

void Enemy::update(std::vector<Bullet>& bullets) {
    shape.move(0, speed); // Bewegung nach unten

    // Zufällige seitliche Bewegung (nur manchmal)
    if (moveClock.getElapsedTime().asSeconds() > 2) {
        if (std::rand() % 2 == 0) { // 50% Chance, sich seitlich zu bewegen
            if (shape.getPosition().x > 0 && shape.getPosition().x < 760) {
                shape.move(moveDirection, 0);
            }
        }
        moveClock.restart();
    }

    // Gegner schießt basierend auf seinem Intervall
    if (shootClock.getElapsedTime().asMilliseconds() > shootInterval) {
        bullets.emplace_back(shape.getPosition().x + 10, shape.getPosition().y + 20, 0.1f, false);
        shootClock.restart();
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Enemy::shoot(std::vector<Bullet>& bullets) {
    bullets.emplace_back(shape.getPosition().x + 10, shape.getPosition().y + 20, 0.1f, false);
}

bool Enemy::isHit(const Bullet& bullet) {
    return bullet.isPlayerBullet && shape.getGlobalBounds().intersects(bullet.shape.getGlobalBounds());
}

void Enemy::takeDamage() {
    health--;
    if (health <= 0) {
        shape.setFillColor(sf::Color::Transparent); // Unsichtbar machen vor der Entfernung
    }
}

bool Enemy::isDead() const {
    return health <= 0;
}