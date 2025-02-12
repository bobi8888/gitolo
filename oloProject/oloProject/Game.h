#pragma once

#include "MainMenuState.h"
#include "GraphicsSettings.h" 

class Game
{
private:
	//Variables
	GraphicsSettings graphicSettings;

	StateData stateData;

	sf::RenderWindow *window;

	sf::Event sfEvent;

	sf::Clock deltaTimeClock;
	float deltaTime;

	std::stack<State*> statesStack;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialization
	void initVariables();
	void initGraphicsSettings();
	void initStateData();
	void initWindow();
	void initStates();
	void initKeys();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Methods
	void endApplication();

	//Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};
