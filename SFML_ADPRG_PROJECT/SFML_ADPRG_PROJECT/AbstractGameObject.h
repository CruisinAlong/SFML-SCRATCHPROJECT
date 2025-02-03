#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class AbstractGameObject
{
public:
	AbstractGameObject(std::string name);
	virtual ~AbstractGameObject();
	virtual void initialize() = 0;
	virtual void processInputs(sf::Event event) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderWindow* window, sf::RenderStates renderStates);
	std::string getName();

	void attachChild(AbstractGameObject* child);
	void detachChild(AbstractGameObject* child);
	void setPosition(float x, float y);
protected:
	sf::Transformable transformable;
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	std::vector<AbstractGameObject*> childList;
};