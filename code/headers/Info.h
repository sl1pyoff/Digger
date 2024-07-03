#pragma once
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include <string>

class Info {
public:
    Info(const std::string& gameName, const std::string& developer, const std::string& info, const std::string& version);
    Info();
    void draw(sf::RenderWindow& window);

private:
    std::string gameName;
    std::string developer;
    std::string info;
    std::string version;

    sf::Font font;
    sf::Text gameNameText;
    sf::Text developerText;
    sf::Text infoText;
    sf::Text versionText;
    sf::Text howToPlayText;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::RectangleShape gameNameBackground;
    sf::RectangleShape developerBackground;
    sf::RectangleShape infoBackground;
    sf::RectangleShape versionBackground;
    sf::RectangleShape howToPlayBackground;
};
