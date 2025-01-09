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
	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pauseMenu;
	std::map<std::string, gui::Button*> buttons;
	TileMap* tileMap;

	sf::IntRect tileToolTextureRect; //the rectangle that is showing which texture of the texture mao
	sf::RectangleShape tileToolSelectorRect; //the rectangle that is visible on the editor

	gui::TextureSelector* textureSelector;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initText();
	void initKeybinds();
	void initButtons();
	void initPauseMenu();
	void initGui();
	void initTileMap();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Methods
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateButtons();
	void updateGUI();
	void updateEditorInput(const float& deltaTime);
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

