#include "headers/Info.h"
#include <iostream>

Info::Info(const std::string& gameName, const std::string& developer, const std::string& info, const std::string& version)
    : gameName(gameName), developer(developer), info(info), version(version) {
    if (!font.loadFromFile("resources/fonts/SecondFont.otf")) {
        std::cerr << "Error, can't load font file" << std::endl;
    }

    gameNameText.setFont(font);
    gameNameText.setString("Game: " + gameName);
    gameNameText.setCharacterSize(30);
    gameNameText.setFillColor(sf::Color::White);
    gameNameText.setPosition(40, 500);

    developerText.setFont(font);
    developerText.setString("Developer: " + developer);
    developerText.setCharacterSize(30);
    developerText.setFillColor(sf::Color::White);
    developerText.setPosition(40, 550);

    infoText.setFont(font);
    infoText.setString("Info: " + info);
    infoText.setCharacterSize(30);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(40, 600);

    versionText.setFont(font);
    versionText.setString("Version: " + version);
    versionText.setCharacterSize(30);
    versionText.setFillColor(sf::Color::White);
    versionText.setPosition(40, 700);

    if (!texture.loadFromFile("resources/images/background.png")) {
        std::cerr << "Error, can't load texture file" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    // Initialize background rectangles
    gameNameBackground.setSize(sf::Vector2f(gameNameText.getLocalBounds().width + 20, gameNameText.getLocalBounds().height + 20));
    gameNameBackground.setFillColor(sf::Color(0, 0, 0, 150));
    gameNameBackground.setPosition(35, 495);

    developerBackground.setSize(sf::Vector2f(developerText.getLocalBounds().width + 20, developerText.getLocalBounds().height + 20));
    developerBackground.setFillColor(sf::Color(0, 0, 0, 150));
    developerBackground.setPosition(35, 545);

    infoBackground.setSize(sf::Vector2f(infoText.getLocalBounds().width + 20, infoText.getLocalBounds().height + 20));
    infoBackground.setFillColor(sf::Color(0, 0, 0, 150));
    infoBackground.setPosition(35, 595);

    versionBackground.setSize(sf::Vector2f(versionText.getLocalBounds().width + 20, versionText.getLocalBounds().height + 20));
    versionBackground.setFillColor(sf::Color(0, 0, 0, 150));
    versionBackground.setPosition(35, 695);
}

Info::Info() {
    if (!font.loadFromFile("resources/fonts/SecondFont.otf")) {
        std::cerr << "Error, can't load font file" << std::endl;
    }

    howToPlayText.setFont(font);
    howToPlayText.setString("1. Use \"W, A, S, D\" to move\n\n W - move towards\n\n S - move backward\n\n A - move left\n\n D - move right\n\n2. Use \"SHIFT\"to run\n\n3. Your main task is to collect\n\nall the bags of gold\n\n4. Try to avoid spiders and\n\nstalagmites. They can kill you\n\n\n\nPress ESCAPE to go back in Main menu");
    howToPlayText.setCharacterSize(35);
    howToPlayText.setFillColor(sf::Color::White);
    howToPlayText.setPosition(100, 220);

    if (!texture.loadFromFile("resources/images/background.png")) {
        std::cerr << "Error, can't load texture file" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    // Initialize background rectangle for howToPlayText
    howToPlayBackground.setSize(sf::Vector2f(howToPlayText.getLocalBounds().width + 200, howToPlayText.getLocalBounds().height + 20));
    howToPlayBackground.setFillColor(sf::Color(0, 0, 0, 150));
    howToPlayBackground.setPosition(0, 215);
}

void Info::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(gameNameBackground);
    window.draw(gameNameText);
    window.draw(developerBackground);
    window.draw(developerText);
    window.draw(infoBackground);
    window.draw(infoText);
    window.draw(versionBackground);
    window.draw(versionText);
    window.draw(howToPlayBackground);
    window.draw(howToPlayText);
}