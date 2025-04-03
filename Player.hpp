#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <vector>

class Player {
public:
    Player();

    // Geänderte Signaturen:
    void handleInput(std::vector<Bullet>& bullets, sf::Clock& clock, float dt);
    void update(float dt);

    void draw(sf::RenderWindow& window);
    void shoot(std::vector<Bullet>& bullets);

    sf::RectangleShape shape;

private:
    sf::Texture playerTexture;
};

#endif
