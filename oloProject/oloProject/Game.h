#pragma once

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *Window;
	sf::Event Event;
	std::vector<sf::VideoMode> VideoModes;
	sf::ContextSettings windowSettings;
	bool isFullscreen;
	sf::Clock deltaTimeClock;
	float deltaTime;

	std::stack<State*> StatesStack;

	std::map<std::string, int> SupportedKeys;

	//Initialization
	void initVariables();
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
