#pragma once
#include "State.h"

class GameState : public State
{
private:
	Player* GameStatePlayer;

	//Initializer Methods
	void initKeybinds();
	void initTextures();
	void initPlayers();

public:
	//Constructors & Destructors
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack);
	virtual ~GameState();

	//Methods
	void updateKeyInput(const float& deltaTime);
	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

