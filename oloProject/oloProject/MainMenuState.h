#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
	//Variables
	sf::Texture BackgroundTexture;
	sf::RectangleShape Background;
	sf::Font Font;

	std::map<std::string, Button*> Buttons;

	//Initializer Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	//Constructors & Destructor
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack);
	virtual ~MainMenuState();

	//Methods
	void updatePlayerInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

};

