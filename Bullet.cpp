// Bullet.cpp
#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float speed, bool isPlayerBullet) : speed(speed), isPlayerBullet(isPlayerBullet) {
    shape.setSize(sf::Vector2f(5, 10));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
}

void Bullet::update() {
    shape.move(0, speed);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}