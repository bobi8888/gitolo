#pragma once

#include "State.h"
#include"GUI.h"
#include"PauseMenu.h"
#include"TileMap.h"

class State;
class GUI;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
	//Variables
	sf::View view;
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

	//Methods
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initButtons();
	void initPauseMenu();
	void initGui();
	void initTileMap();

public:
	//Constructors & Desctructor
	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Methods
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateButtons();
	void updateGUI(const float& deltaTime);
	void updateEditorInput(const float& deltaTime);
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

