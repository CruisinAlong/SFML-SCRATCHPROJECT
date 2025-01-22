#include <SFML/Graphics.hpp>
#include "Game.h"
#include "TextureManager.h"
#include <iostream>

int main() {
    std::cout << "Game is starting..." << std::endl;
    Game game;
    game.run();
    std::cout << "Game has ended." << std::endl;
}

// Game constructor
Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Application"), mSampleEntity() {
    std::cout << "Initializing Game..." << std::endl;
    mWindow.setFramerateLimit(60);

    sf::Texture mTexture;
	if (!mTexture.loadFromFile("C:/Users/USER/source/repos/SFML_ADPRG_PROJECT/SFML_ADPRG_PROJECT/Media/Textures/Eagle.png")) {
		std::cout << "No texture detected!" << std::endl;
	}
    mSampleEntity.setTexture(mTexture);
    mSampleEntity.getSprite()->setPosition(100.f,100.f); 

    TextureManager::getInstance()->loadAll();

	addEntity("bed_0", 0.f, 0.f);
	addEntity("bench_0", 150.f, 0.f);
	addEntity("gift_0", 300.f, 0.f);
	addEntity("coin_0", 450.f, 0.f);

    // Load font and initialize FPS text
    if (!mFont.loadFromFile("C:/Users/USER/source/repos/SFML_ADPRG_PROJECT/SFML_ADPRG_PROJECT/Media/Fonts/Sansation.ttf")) {
        std::cout << "No font detected! " << std::endl;
    }
    mText.setFont(mFont);
    mText.setCharacterSize(16);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(10.f, 10.f);

    mText2.setFont(mFont);
    mText2.setCharacterSize(16);
    mText2.setFillColor(sf::Color::White);
    mText2.setPosition(10.f, 30.f);



    std::cout << "Game initialization complete." << std::endl;
}

void Game::addEntity(std::string key, float x, float y) {
	sf::Texture* texture = TextureManager::getInstance()->getTexture(key);
	Entity* entity = Entity::createEntity(TextureManager::getInstance()->getTexture(key), x, y);
	mEntityList.push_back(entity);
}

// Main game loop
void Game::run() {
    std::cout << "Entering game loop..." << std::endl;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time elapsedTime;
	TextureManager::getInstance()->testFunction();

    while (mWindow.isOpen()) {
        processEvents();
        elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        // Calculate FPS using stringstream to make use of variables in the window
        float fps = 1.f / elapsedTime.asSeconds();
        std::stringstream fpsStream;
        fpsStream << "FPS: " << static_cast<int>(fps);
        mText.setString(fpsStream.str());

        std::stringstream deltaTimeStream;
        deltaTimeStream << "DeltaTime: " << elapsedTime.asSeconds() << " s";
        mText2.setString(deltaTimeStream.str());

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
    std::cout << "Exiting game loop..." << std::endl;
}

// Event handling
void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            std::cout << "Key pressed: " << event.key.code << std::endl;
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            std::cout << "Key released: " << event.key.code << std::endl;
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
                mTargetPosition = mWindow.mapPixelToCoords(mousePosition);
                mIsMovingToTarget = true;

                // Calculate angle to face the target
                sf::Vector2f spritePosition = mSampleEntity.getSprite()->getPosition();
                sf::Vector2f direction = mTargetPosition - spritePosition;
                float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
                mSampleEntity.getSprite()->setRotation(angle + 90.f); // Adjust for default orientation
            }
            break;
        case sf::Event::Closed:
            std::cout << "Window closed event triggered." << std::endl;
            mWindow.close();
            break;
        }
    }
}

// Render function
void Game::render() {
    mWindow.clear();
    mWindow.draw(*mSampleEntity.getSprite());
    for (int i = 0; i < mEntityList.size(); i++) {
        mWindow.draw(*mEntityList[i]->getSprite());
    }
    mWindow.draw(mText);
    mWindow.draw(mText2);
    mWindow.display();
}

// Handle player input
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    sf::Vector2f direction(0.f, 0.f);

    switch (key) {
    case sf::Keyboard::W:
        mIsMovingUp = isPressed;
        std::cout << "Is moving Up!" << std::endl;
        direction.y -= 1.f;
        break;
    case sf::Keyboard::A:
        mIsMovingLeft = isPressed;
        std::cout << "Is moving Left!" << std::endl;
        direction.x -= 1.f;
        break;
    case sf::Keyboard::S:
        mIsMovingDown = isPressed;
        std::cout << "Is moving Down!" << std::endl;
        direction.y += 1.f;
        break;
    case sf::Keyboard::D:
        mIsMovingRight = isPressed;
        std::cout << "Is moving Right!" << std::endl;
        direction.x += 1.f;
        break;
    }
    if (direction.x != 0.f || direction.y != 0.f) {
        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f; // Convert radians to degrees
        mSampleEntity.getSprite()->setRotation(angle + 90.f); // Adjust for default sprite orientation
    }
}

// Update logic
void Game::update(sf::Time deltaTime) {

     sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;
    if (mIsMovingToTarget) {
        sf::Vector2f currentPosition = mSampleEntity.getSprite()->getPosition();
        sf::Vector2f direction = mTargetPosition - currentPosition;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 1.f) { // Stop when close enough to the target
            direction /= distance; // Normalize direction
            movement += direction * PlayerSpeed;
        }
        else {
            mIsMovingToTarget = false;
        }
    }

    mSampleEntity.getSprite()->move(movement * deltaTime.asSeconds());
    

}
