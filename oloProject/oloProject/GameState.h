#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "TransitionComponent.h"
#include "ParticleTrickle.h"

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
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;

	sf::Sprite renderSprite;

	//sf::RenderStates mainRenderState;
	sf::Shader mainShader;
	sf::Shader dustShader;
	ParticleTrickle dustParticles;
	sf::Clock gameClock;
	sf::RenderStates mainRenderState;

	sf::Font font;
	sf::Text cursorText;

		sf::Texture testTexture;
		sf::Sprite testSprite;

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
	void initTileMap();
	void initPlayerGUI();
	
	void initTransitionComponents();

public:
	//Constructors & Destructors
	GameState(StateData* stateData, std::string name);

	virtual ~GameState();

	//Update Methods
	void updateTransitions(const float& deltaTime);

	void updateShaders();

	//void updateView(const float& deltaTime);
	void updateView();

	//void updateInput(const float& deltaTime);
	void updateInput();

	void updatePlayerInput(const float& deltaTime);

	//void updatePlayerGUI(const float& deltaTime);

	void updatePauseMenuButtons();

	void updateTileMap(const float& deltaTime);

	void update(const float& deltaTime);

	void render(sf::RenderTarget* target = NULL);
};

