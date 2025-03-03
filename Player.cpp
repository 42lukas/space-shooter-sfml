// Player.cpp
#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player() {
    shape.setSize(sf::Vector2f(50, 50));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(400, 550);
}

void Player::handleInput(std::vector<Bullet>& bullets, sf::Clock& clock) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shape.getPosition().x > 0) {
        shape.move(-0.2f, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && shape.getPosition().x < 750) {
        shape.move(0.2f, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (clock.getElapsedTime().asMilliseconds() > 100) { // 100ms Schuss-Delay
            bullets.emplace_back(shape.getPosition().x + 20, shape.getPosition().y, -0.1f, true); // true = Player Bullet
            clock.restart();
        }
    }
}

void Player::update() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}