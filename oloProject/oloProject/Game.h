#pragma once

#include "MainMenuState.h"
#include "GraphicsSettings.h" 

class Game
{
private:
	//Variables
	GraphicsSettings GameGraphicSettings;
	sf::RenderWindow *Window;
	sf::Event Event;

	sf::Clock deltaTimeClock;
	float deltaTime;

	std::stack<State*> StatesStack;

	std::map<std::string, int> SupportedKeys;

	//Initialization
	void initVariables();
	void initGraphicsSettings();
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
