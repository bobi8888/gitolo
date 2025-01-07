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
	PauseMenu* pauseMenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap tileMap;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initPauseMenu();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	//Methods
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

