#pragma once

#include "State.h"
#include"GUI.h"
#include"PauseMenu.h"
#include"TileMap.h"

class State;
class GUI;
class PauseMenu;
class TileMap;

class sf::RenderTexture;

class EditorState :
    public State


{
private:
	//Variables
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	sf::Shader mainShader;

		sf::Texture* testTile;
		sf::Texture* testPlayerTexture;
		sf::Sprite* testPlayer; 
		float speed = 0.2f;
		sf::Vector2f movement;
		sf::Vector2i lightScreenPosition;
		std::vector<sf::Sprite*> backgroundTiles;

		sf::VertexArray* vertices;
		sf::VertexBuffer* vertexBuffer;

	sf::Font font;
	sf::Text cursorText;

	sf::RectangleShape sideBar;
	sf::IntRect tileToolTextureRect; //the rectangle that is showing which texture of the texture mao
	sf::RectangleShape tileToolSelectorRect; //the rectangle that is visible on the editor

	PauseMenu* pauseMenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	gui::TextureSelector* textureSelector;

	int layer;
	float cameraSpeed;
	bool collision;
	short type;
	bool tileAddLock;

	//Methods
	void initRender();
	void initVariables();
	void initView();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	//void initShaders();
	void initTileMap();
	void initGui();

public:
	sf::RectangleShape lightOverlay;
	sf::Shader lightShader;
	sf::RectangleShape background;
	sf::Texture dummyTexture;


	//Constructors & Desctructor
	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Update Methods
	void updatePauseMenuButtons();

	void updatePlayerInput(const float& deltaTime);

	void updateButtons();

	void updateGUI(const float& deltaTime);

	void updateEditorInput(const float& deltaTime);

	void update(const float& deltaTime);

	//Render Methods
	void renderButtons(sf::RenderTarget& target);

	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = NULL);
};

