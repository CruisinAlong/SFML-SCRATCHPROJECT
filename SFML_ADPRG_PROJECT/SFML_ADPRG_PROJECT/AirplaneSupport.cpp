#include "AirplaneSupport.h"
#include "TextureManager.h"
#include <cmath>
#include <iostream>

const float SPEED = 100.f;
const float FREQUENCY = 2.0f;

AirplaneSupport::AirplaneSupport(std::string name) : AbstractGameObject(name),  elapsedTime(0.0f) {
    if (name == "AirSupport_1") {
        direction = -1.0f;
    }
    else if (name == "AirSupport_2") {
        direction = 1.0f;
    }
}

void AirplaneSupport::initialize() {
    this->sprite = new sf::Sprite();
    sf::Texture* texture = TextureManager::getInstance()->getTexture("raptor");
    this->sprite->setTexture(*texture);
    sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
    this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    this->sprite->setPosition(0, 0);
}

void AirplaneSupport::processInputs(sf::Event event) {
    // No input processing needed for support planes
}

void AirplaneSupport::update(sf::Time deltaTime) {
    if (name == "AirSupport_1") {
        elapsedTime += deltaTime.asSeconds();
        if (elapsedTime >= 3.0f) {
            direction *= -1;
            elapsedTime = 0.f;
            std::cout << "1: Reversed Direction " << direction << std::endl;
        }

    }
    else if (name == "AirSupport_2") {
        sf::Vector2f position = this->transformable.getPosition();
        elapsedTime += deltaTime.asSeconds();
        if (elapsedTime >= 3.0f) {
            direction *= -1;
            elapsedTime = 0.f;
            std::cout << "2: Reversed Direction " << direction << std::endl;
        }
    }
    float deltaSeconds = deltaTime.asSeconds();
    float movement = SPEED * deltaSeconds * direction;
    // Move the airplane side to side
    this->transformable.move(movement, 0);

}
