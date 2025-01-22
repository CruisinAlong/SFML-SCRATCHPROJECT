#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

TextureManager* TextureManager::instance = NULL;

TextureManager* TextureManager::getInstance() {
	if (instance == NULL) {
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::testFunction() {
	std::cout << "Hi im singleton! ;)" << std::endl;
}

void TextureManager::loadAll() {
	for (int i = 0; i < 8; i++) {
		std::string str_i = std::to_string(i);
		loadTexture("bed_" + str_i, "Media/Textures/bed000" + str_i + ".png");
		loadTexture("bench_" + str_i, "Media/Textures/bench000" + str_i + ".png");
		loadTexture("gift_" + str_i, "Media/Textures/boxGift_000" + str_i + ".png");
		loadTexture("coin_" + str_i, "Media/Textures/coin000" + str_i + ".png");
	}
}

void TextureManager::loadTexture(std::string key , std::string path) {
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}

sf::Texture* TextureManager::getTexture(std::string key) {
	if (textureMap[key] != nullptr) {
		return textureMap[key];
	}
	else {
		std::cout << "No texture found for " << key << std::endl;
		return nullptr;
	}
}