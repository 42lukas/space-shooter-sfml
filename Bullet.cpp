#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float speed, bool isPlayerBullet)
    : speed(speed), isPlayerBullet(isPlayerBullet)
{
    shape.setSize(sf::Vector2f(5, 10));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
}

void Bullet::update(float dt) {
    // speed in Pixel pro Sekunde, daher Multiplikation mit dt
    shape.move(0.f, speed * dt);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
