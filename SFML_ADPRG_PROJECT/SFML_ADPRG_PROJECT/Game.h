#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

#include <sstream>


class Game {
public:
	Game();
	void run();
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

private:
	void processEvents();
	void update(sf::Time);
	void render();
	void handlePlayerInput(sf::Keyboard::Key, bool);
	void addEntity(std::string key, float x, float y);

private:
	sf::RenderWindow mWindow;
	Entity mSampleEntity;
	std::vector<Entity*> mEntityList;


private:
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
	float PlayerSpeed = 300.0f;

private:
	sf::Text mText;
	sf::Text mText2;
	sf::Font mFont;

private:
	sf::Vector2f mTargetPosition;
	bool mIsMovingToTarget = false;



};