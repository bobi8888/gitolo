#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class PauseMenu;
class TileMap;

class GameState : public State
{
private:
	sf::Font font;
	PauseMenu* pauseMenu;
	Player* player;
	//Missing a texture here?
	TileMap* tileMap;
	const sf::IntRect texture_rect;

	//Initializer Methods
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	//Constructors & Destructors
	GameState(StateData* stateData);
	virtual ~GameState();

	//Methods
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void updatePauseMenuButtons();
	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

