#pragma once

#include "State.h"
#include "GraphicsSettings.h"
#include "GUI.h"

class State;
class GraphicsSettings;
class GUI;

class SettingsState :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;
	sf::Text text;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropdownList*> dropdownMap;

	std::vector<sf::VideoMode> videoModes;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGUI();
	void initText();

public:
    //Constructors & Destructor
    SettingsState(StateData* stateData);
    virtual ~SettingsState();

    //Accessor Methods

    //Methods
	void updatePlayerInput(const float& deltaTime);
	void updateGUI(const float& deltaTime);
	void update(const float& deltaTime);	
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

