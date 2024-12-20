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
	sf::Text MenuText;
	sf::RectangleShape Background;
	sf::RectangleShape Container;
	std::map<std::string, Button*> Buttons;

	//Private Methods

public:
	//Constructors & Desctructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor Methods
	std::map<std::string, Button*>& getButtons();

	//Methods
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, const std::string text, float xPos, float yPos);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);

	sf::RectangleShape getContainer();
};

