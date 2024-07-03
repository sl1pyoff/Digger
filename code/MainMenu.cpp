#include "headers/MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("resources/fonts/MainFont.otf")) {
		std::cout << "No font is here";
	}

	// Play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("New Game");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(850, 400);

	// Options
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("How to Play");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(850, 500);

	// About
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("About");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(850, 600);

	// Exit
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::White);
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(850, 700);

	MainMenuSelected = 0; // Встановимо вибраний елемент на перший елемент
	mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow); // Перший елемент виділений
}

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; ++i)
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

	if (MainMenuSelected - 1 >= 0)
	{
		MainMenuSelected--;
	}
	else
	{
		MainMenuSelected = Max_main_menu - 1;
	}

	mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);
}

void MainMenu::MoveDown()
{
	mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

	if (MainMenuSelected + 1 < Max_main_menu)
	{
		MainMenuSelected++;
	}
	else
	{
		MainMenuSelected = 0;
	}

	mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);
}

MainMenu::~MainMenu()
{
}