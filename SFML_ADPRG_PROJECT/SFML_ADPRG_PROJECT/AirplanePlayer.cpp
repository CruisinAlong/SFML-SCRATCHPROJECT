#include "AirplanePlayer.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"

AirplanePlayer::AirplanePlayer(std::string name) : AbstractGameObject(name)
{
}

void AirplanePlayer::initialize()
{
	std::cout << "AirplanePlayer initialized" << std::endl;
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("eagle"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}

void AirplanePlayer::processInputs(sf::Event event) {
	bool keyFlag = false;
	if (event.type == sf::Event::KeyPressed) {
		keyFlag = true;
	}
	else if (event.type == sf::Event::KeyReleased) {
		keyFlag = false;
	}

	switch (event.key.code) {
	case sf::Keyboard::W:
		this->moveUp = keyFlag;
		break;
	case sf::Keyboard::A:
		this->moveLeft = keyFlag;
		break;
	case sf::Keyboard::S:
		this->moveDown = keyFlag;
		break;
	case sf::Keyboard::D:
		this->moveRight = keyFlag;
		break;
	}
}

void AirplanePlayer::update(sf::Time deltaTime) {
    sf::Vector2f offset(0.0f, 0.0f);
    
    // Handle WASD movement
    if (this->moveUp) {
        offset.y -= this->SPEED_MULTIPLIER;
    }
    if (this->moveDown) {
        offset.y += this->SPEED_MULTIPLIER;
    }
    if (this->moveRight) {
        offset.x += this->SPEED_MULTIPLIER;
    }
    if (this->moveLeft) {
        offset.x -= this->SPEED_MULTIPLIER;
    }
    this->transformable.move(offset * deltaTime.asSeconds());

    // Call the base class update to update child objects
    AbstractGameObject::update(deltaTime);
}
