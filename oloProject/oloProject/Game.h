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

	//Initialization
	void initWindow();
	void initStates();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Methods
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};
