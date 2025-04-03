#include "Enemy.hpp"
#include <cstdlib>

Enemy::Enemy(float x, float y, int health, float speed, int shootInterval)
    : health(health)
    , speed(speed)
    , shootInterval(shootInterval)
{
    shape.setRadius(20);
    // Tanks (health > 1) = Blau, sonst Rot
    shape.setFillColor(health > 1 ? sf::Color::Blue : sf::Color::Red);
    shape.setPosition(x, y);

    shootClock.restart(); // Schusstimer
    moveClock.restart();  // Optionaler Bewegungstimer für komplexere Patterns
}

// updated die Position und das Verhalten des Gegners
void Enemy::update(std::vector<Bullet>& bullets, float dt) {
    // Bewegung nach unten
    // Bei speed=60.f z.B. ~60 Pixel pro Sekunde
    shape.move(0.f, speed * dt);

    // Schießen (falls Intervall überschritten)
    shoot(bullets);
}

// Erstellt eine Kugel, wenn der Gegner schießen darf
void Enemy::shoot(std::vector<Bullet>& bullets) {
    if (shootClock.getElapsedTime().asMilliseconds() > shootInterval) {
        // Feuert eine Bullet nach unten ab
        bullets.emplace_back(
            shape.getPosition().x + 10.f,
            shape.getPosition().y + 20.f,
            400.f,            // Bullet-Speed
            false             // isPlayerBullet
        );
        shootClock.restart();
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Check: von Spieler-Kugel getroffen?
bool Enemy::isHit(const Bullet& bullet) {
    return bullet.isPlayerBullet
        && shape.getGlobalBounds().intersects(bullet.shape.getGlobalBounds());
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
