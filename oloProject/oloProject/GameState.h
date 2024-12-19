#pragma once
#include "State.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	sf::Font Font;
	PauseMenu PauseMenu;
	Player* GameStatePlayer;
	//Missing a texture here?

	//Initializer Methods
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPlayers();

public:
	//Constructors & Destructors
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack);
	virtual ~GameState();

	//Methods
	void updatePausedInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

