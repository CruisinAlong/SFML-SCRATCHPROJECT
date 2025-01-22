#include "Entity.h"

Entity::Entity() {
}

void Entity::setTexture(sf::Texture texture) {
    mTexture = texture;
    mPlayer.setTexture(texture);
}

sf::Sprite* Entity::getSprite() {
    return &mPlayer;
}
Entity* Entity::createEntity(sf::Texture* tex, float x, float y) {
	Entity* entity = new Entity();
	entity->setTexture(*tex);
	entity->getSprite()->setPosition(x, y);
	return entity;
}
