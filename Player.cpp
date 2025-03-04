#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player() {
    shape.setSize(sf::Vector2f(75, 75));
    shape.setPosition(350, 550);

    if (!playerTexture.loadFromFile("assets/player.png")) {
        std::cerr << "Fehler beim Laden der Spielertextur!" << std::endl;
    }
    shape.setTexture(&playerTexture);
}

// user Tastatureingaben
void Player::handleInput(std::vector<Bullet>& bullets, sf::Clock& clock) {
    // links <-- a
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shape.getPosition().x > 0) {
        shape.move(-0.2f, 0);
    }
    // d --> rechts
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && shape.getPosition().x < 750) {
        shape.move(0.2f, 0);
    }
    // player schießt
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clock.getElapsedTime().asMilliseconds() > 100) {
        bullets.emplace_back(shape.getPosition().x + 37.5f, shape.getPosition().y, -0.1f, true);
        clock.restart();
    }
}

void Player::update() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
