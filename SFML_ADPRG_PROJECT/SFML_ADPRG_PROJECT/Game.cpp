#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

Game::Game() : mWindow(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_WIDTH), "SFML Application")
{
	std::cout << "Game constructor called" << std::endl;
	mWindow.setFramerateLimit(60);
	TextureManager::getInstance()->loadAll();

	BGObject* bgObject = new BGObject("bgObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
	GameObjectManager::getInstance()->addObject(planeObject);

	AirplaneSupport* support1 = new AirplaneSupport("AirSupport_1");
	planeObject->attachChild(support1);
	support1->setPosition(50, 100);

	AirplaneSupport* support2 = new AirplaneSupport("AirSupport_2");
	planeObject->attachChild(support2);
	support2->setPosition(-50, 100);

}

void Game::addEntity(std::string key, float x, float y)
{
	sf::Texture* tex = TextureManager::getInstance()->getTexture(key);
	Entity* entity = Entity::createEntity(tex, x, y);
	mEntitiyList.push_back(entity);
}

void Game::run()
{
	std::cout << "Game run started" << std::endl;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}

		update(deltaTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			std::cout << "Window closed event" << std::endl;
			mWindow.close();
			break;
		default:
			GameObjectManager::getInstance()->processInput(event);
			break;
		}
	}
}

void Game::render() {
	mWindow.clear();
	GameObjectManager::getInstance()->draw(&mWindow);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	std::cout << "Handling player input: key=" << key << ", isPressed=" << isPressed << std::endl;
	switch (key) {
	case sf::Keyboard::W:
		mIsMovingUp = isPressed;
		break;
	case sf::Keyboard::S:
		mIsMovingDown = isPressed;
		break;
	case sf::Keyboard::A:
		mIsMovingLeft = isPressed;
		break;
	case sf::Keyboard::D:
		mIsMovingRight = isPressed;
		break;
	}
}

void Game::update(sf::Time deltaTime) {
	GameObjectManager::getInstance()->update(deltaTime);
}
