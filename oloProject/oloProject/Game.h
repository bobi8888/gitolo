#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#ifndef GAME_H
#define GAME_H


class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event Event;

	//Initialization
	void initWindow();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Methods
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};

#endif // !GAME_H