#pragma once

#include "State.h"
#include "GraphicsSettings.h"
#include "GUI.h"

class SettingsState :
    public State
{
private:
	//Variables
	GraphicsSettings& SettingsGraphicsSettings;

	sf::Texture BackgroundTexture;
	sf::RectangleShape Background;

	sf::Font Font;
	sf::Text OptionsText;

	std::map<std::string, gui::Button*> Buttons;
	std::map<std::string, gui::DropdownList*> DropdownMap;

	std::vector<sf::VideoMode> VideoModes;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGUI();
	void initText();

public:
    //Constructors & Destructor
    SettingsState(
		sf::RenderWindow* window, 
		GraphicsSettings& graphicsSettings,
		std::map<std::string, 
		int>* supportedKeys, 
		std::stack<State*>* statesStack
	);
    virtual ~SettingsState();

    //Accessor Methods

    //Methods
	void updatePlayerInput(const float& deltaTime);
	void updateGUI(const float& deltaTime);
	void update(const float& deltaTime);	
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

