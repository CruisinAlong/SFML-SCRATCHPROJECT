#include "BGObject.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

BGObject::BGObject(std::string name) : AbstractGameObject(name)
{
}

void BGObject::initialize()
{
    std::cout << "BGObject initialized" << std::endl;

    sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 8));
    sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);
}

void BGObject::update(sf::Time deltaTime)
{
    sf::Vector2f offset(0.0f, 0.0f);
    offset.y += SPEED_MULTIPLIER;
    sprite->move(offset * deltaTime.asSeconds());

    sf::Vector2f localPos = sprite->getPosition();
    if (localPos.y * deltaTime.asSeconds() > 0) {
        sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);
    }
}

void BGObject::processInputs(sf::Event event)
{
}


