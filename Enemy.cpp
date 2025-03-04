#include "Enemy.hpp"
#include <cstdlib>
using namespace std;

Enemy::Enemy(float x, float y, int health, float speed, int shootInterval)
    : health(health), speed(speed), shootInterval(shootInterval) {

    shape.setRadius(20);
    shape.setFillColor(health > 1 ? sf::Color::Blue : sf::Color::Red); // Tanks sind Blau, normale Gegner Rot
    shape.setPosition(x, y);

    shootClock.restart(); // Startet den shooting Timer
    moveClock.restart(); // Startet den movement Timer
}

// updated die Position und das Verhalten des Gegners
void Enemy::update(std::vector<Bullet>& bullets) {
    shape.move(0, speed);
    shoot(bullets);
}

// Erstellt eine Kugel, wenn der Gegner schieﬂen soll
void Enemy::shoot(std::vector<Bullet>& bullets) {
    if (shootClock.getElapsedTime().asMilliseconds() > shootInterval) {
        bullets.emplace_back(shape.getPosition().x + 10, shape.getPosition().y + 20, 0.1f, false);
        shootClock.restart();
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// checkt, ob der Gegner von einer Spieler-Kugel getroffen wurde
bool Enemy::isHit(const Bullet& bullet) {
    return bullet.isPlayerBullet && shape.getGlobalBounds().intersects(bullet.shape.getGlobalBounds());
}

void Enemy::takeDamage() {
    health--;
    if (health <= 0) {
        shape.setFillColor(sf::Color::Transparent);
    }
}

bool Enemy::isDead() const {
    return health <= 0;
}