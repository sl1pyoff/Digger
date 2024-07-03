#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define Max_main_menu 4

class MainMenu
{
public:
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}

	~MainMenu();
private:
	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
};
