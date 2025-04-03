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

// user Tastatureingaben (jetzt zeitbasiert über dt)
void Player::handleInput(std::vector<Bullet>& bullets, sf::Clock& clock, float dt) {
    // Definiere eine konstante Geschwindigkeit in Pixeln pro Sekunde
    const float moveSpeed = 300.f;

    // links <-- a
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shape.getPosition().x > 0) {
        // moveSpeed * dt nach links
        shape.move(-moveSpeed * dt, 0);
    }
    // d --> rechts
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && shape.getPosition().x < 750) {
        // moveSpeed * dt nach rechts
        shape.move(moveSpeed * dt, 0);
    }

    // player schießt
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
        && clock.getElapsedTime().asMilliseconds() > 100)
    {
        // Kugel (Bullet) fliegt mit -300 px/s nach oben (Beispiel)
        bullets.emplace_back(
            shape.getPosition().x + 37.5f,
            shape.getPosition().y,
            -300.f,    // Bullet-Speed
            true       // isPlayerBullet
        );
        clock.restart();
    }
}

void Player::update(float dt) {
    // Aktuell keine Logik – könnte z.B. Animationen enthalten
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
