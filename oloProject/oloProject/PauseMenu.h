#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include "Button.h";
class PauseMenu
{
private:
	sf::Font& Font;
	sf::Text Text;
	sf::RectangleShape Background;
	sf::RectangleShape Container;

	std::map<std::string, Button*> Buttons;

public:
	//Constructors & Desctructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Methods
	void update();
	void render(sf::RenderTarget& target);
};

