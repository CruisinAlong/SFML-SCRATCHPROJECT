#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "AirplaneSupport.h"

class Game {
public:
	Game();
	void run();
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
public:
	static const int WINDOW_WIDTH = 640;
	static const int WINDOW_HEIGHT = 480;
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool);
	void addEntity(std::string key, float x, float y);
private: 
	std::vector<Entity*> mEntitiyList;
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	Entity mSampleEntity;
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
	float PlayerSpeed = 300.f;
};