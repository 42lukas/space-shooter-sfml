// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"
#include <vector>

class Player {
public:
    Player();
    void handleInput(std::vector<Bullet>& bullets, sf::Clock& clock);
    void update();
    void draw(sf::RenderWindow& window);
    void shoot(std::vector<Bullet>& bullets);

    sf::RectangleShape shape;
};

#endif
