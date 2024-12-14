#pragma once

#include "GameState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event Event;

	sf::Clock deltaTimeClock;
	float deltaTime = 0.f;

	std::stack<State*> States;

	std::map<std::string, int> SupportedKeys;

	//Initialization
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
