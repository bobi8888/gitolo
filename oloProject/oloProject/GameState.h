#pragma once
#include "State.h"

class GameState : public State
{
private:

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	//Methods
	void endState();
	void updateKeybinds(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

