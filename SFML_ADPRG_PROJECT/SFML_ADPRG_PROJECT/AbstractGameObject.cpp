#include "AbstractGameObject.h"

AbstractGameObject::AbstractGameObject(std::string name)
{
	this->name = name;
}

AbstractGameObject::~AbstractGameObject()
{
	if (this->sprite != NULL) {
		delete this->sprite;
	}
}

std::string AbstractGameObject::getName()
{
	return name;
}

void AbstractGameObject::draw(sf::RenderWindow* window, sf::RenderStates renderStates)
{
	renderStates.transform = renderStates.transform * this->transformable.getTransform();
	
	window->draw(*sprite, renderStates);

	for (int i = 0; i < this->childList.size(); i++)
	{
		AbstractGameObject* child = this->childList[i];
		child->draw(window, renderStates);
	}
}

void AbstractGameObject::attachChild(AbstractGameObject* child)
{
	this->childList.push_back(child);
	child->initialize();
}

void AbstractGameObject::detachChild(AbstractGameObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++)
	{
		if (this->childList[i] == child)
		{
			index = i;
		}
	}

	if (index != -1)
	{
		this->childList.erase(this->childList.begin() + index);
		this->childList.shrink_to_fit();
	}
}

void AbstractGameObject::setPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}

void AbstractGameObject::update(sf::Time deltaTime) {
	for (auto* child : childList) {
		child->update(deltaTime);
	}
}

