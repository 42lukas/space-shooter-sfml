#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <vector>

class Enemy {
public:
    Enemy(float x, float y, int health = 1, float speed = 175.0f, int shootInterval = 500);

    // Update-Methode mit dt
    void update(std::vector<Bullet>& bullets, float dt);
    void draw(sf::RenderWindow& window);
    void shoot(std::vector<Bullet>& bullets);
    bool isHit(const Bullet& bullet);
    void takeDamage();
    bool isDead() const;

    sf::CircleShape shape;
    sf::Clock shootClock;
    sf::Clock moveClock;
    float moveDirection;
    int health;
    float speed;
    int shootInterval;
};

#endif
