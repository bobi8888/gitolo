#pragma once

#include "State.h"
#include "GUI.h"

class SettingsState :
    public State
{
private:
	//Variables
	sf::Texture BackgroundTexture;
	sf::RectangleShape Background;
	sf::Font Font;

	std::map<std::string, gui::Button*> Buttons;

	gui::DropdownList* ddl;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
    //Constructors & Destructor
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack);
    virtual ~SettingsState();

    //Accessor Methods

    //Methods
	void updatePlayerInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);	
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

