#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class State;
class PauseMenu;
class TileMap;
class Player;
class PlayerGUI;

class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState : public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	sf::Text cursorText;

	PauseMenu* pauseMenu;
	Player* player;
	PlayerGUI* playerGUI;
	//Missing a texture here?
	TileMap* tileMap;
	const sf::IntRect texture_rect;

	//Initializer Methods
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initPlayerGUI();
	void initTileMap();

public:
	//Constructors & Destructors
	GameState(StateData* stateData);
	virtual ~GameState();

	//Methods
	void updateView(const float& deltaTime);
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void updatePlayerGUI(const float& deltaTime);
	void updatePauseMenuButtons();
	void updateTileMap(const float& deltaTime);
	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

