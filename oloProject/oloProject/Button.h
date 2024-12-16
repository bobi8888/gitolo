#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/OpenGL.hpp>

#include<iostream>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned ButtonState;

	sf::RectangleShape Rectangle;
	sf::Font* Font;
	sf::Text Text;

	sf::Color IdleColor;
	sf::Color HoverColor;
	sf::Color ActiveColor;

public:	
	Button();
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	//Accessors
	const bool isPressed() const;

	//Methods
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

