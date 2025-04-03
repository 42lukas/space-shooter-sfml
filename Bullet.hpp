#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, float speed, bool isPlayerBullet);
    // Update mit Delta Time:
    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::RectangleShape shape;
    float speed;
    bool isPlayerBullet; // True = Player Bullet, False = Enemy Bullet
};

#endif
