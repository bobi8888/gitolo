#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "GraphicsSettings.h"
#include "GUI.h"

class GameState;
class EditorState;
class SettingsState;
class GraphicsSettings;
class GUI;

class MainMenuState :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font Font;

	std::map<std::string, gui::Button*> buttons;

	//Initializer Methods
	void initVariables();

	void initFonts();

	void initKeybinds();

	void initGUI();

	void resetGUI();

public:
	//Constructors & Destructor
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	//Methods
	void updatePlayerInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

