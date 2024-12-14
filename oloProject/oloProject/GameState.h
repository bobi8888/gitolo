#pragma once
#include "State.h"

class GameState : public State
{
private:
	Entity Entity;

	//Methods
	void initKeybinds();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	//Methods
	void endState();

	void updateKeyInput(const float& deltaTime);
	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

