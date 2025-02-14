#pragma once

#include "GUI.h"

class GUI;

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text text;
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*> buttons;

	//Private Methods

public:
	//Constructors & Desctructor
	PauseMenu(sf::VideoMode& videoMode,sf::Font& font);

	virtual ~PauseMenu();

	//Accessor Methods
	std::map<std::string, gui::Button*>& getButtons();

	//Methods
	const bool isButtonPressed(const std::string key);

	void addButton(
		const float xPos, const float yPos, 
		const float width, const float height,
		const std::string key, const std::string text, const unsigned char_size 		
	);

	void update(const sf::Vector2i& mousePosWindow);

	void render(sf::RenderTarget& target);

	sf::RectangleShape getContainer();
};

