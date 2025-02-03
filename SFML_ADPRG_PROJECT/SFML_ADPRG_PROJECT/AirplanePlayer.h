#pragma once
#include "AbstractGameObject.h"

class AirplanePlayer : public AbstractGameObject
{
public:
	AirplanePlayer(std::string name);
	void initialize() override;
	void update(sf::Time deltaTime);
	void processInputs(sf::Event event) override;
private:
	const float SPEED_MULTIPLIER = 300.f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	float direction = 1.0f;
};