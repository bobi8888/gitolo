#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "TransitionComponent.h"

class State;
class PauseMenu;
class TileMap;
class Player;
class PlayerGUI;
class TransitionComponent;

class sf::View;
class sf::Font;
class sf::RenderTexture;
class sf::Shader;

class GameState : public State
{
private:
	std::string name;

	sf::View view;
	sf::RenderTexture renderTexture;

	sf::Sprite renderSprite;

	sf::Shader mainShader;

	sf::Font font;
	sf::Text cursorText;

	//is this needed?
	PauseMenu* pauseMenu;

	Player* player;
	PlayerGUI* playerGUI;

	//Missing a texture here?
	TileMap* tileMap;
	const sf::IntRect texture_rect;

	TransitionComponent* transitionComponent;

	//Initializer Methods
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initTileMap();
	void initTransitionComponents();

public:
	//Constructors & Destructors
	GameState(StateData* stateData, std::string name);

	virtual ~GameState();

	//Methods
	void updateView(const float& deltaTime);

	void updateInput(const float& deltaTime);

	void updatePlayerInput(const float& deltaTime);

	//void updatePlayerGUI(const float& deltaTime);

	void updatePauseMenuButtons();

	void updateTileMap(const float& deltaTime)
	;
	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

