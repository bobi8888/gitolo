#pragma once

#include "GUI.h";

class GUI;

class PauseMenu
{
private:
	sf::Font& Font;
	sf::Text MenuText;
	sf::RectangleShape Background;
	sf::RectangleShape Container;
	std::map<std::string, gui::Button*> Buttons;

	//Private Methods

public:
	//Constructors & Desctructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor Methods
	std::map<std::string, gui::Button*>& getButtons();

	//Methods
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, const std::string text, float xPos, float yPos);
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);

	sf::RectangleShape getContainer();
};

