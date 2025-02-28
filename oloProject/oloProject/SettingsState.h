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

	std::vector<std::string> valid_Resolutions = {
	"1920 x 1080",
	"1760 x 990",
	"1680 x 1050",
	"1660 x 900",
	"1366 x 786",
	"1280 x 1024",
	"1280 x 720",
	"1128 x 634",
	"1024 x 768",
	"800 x 600",
	"720 x 576",
	"720 x 480",
	"640 x 480"
	};

	//Methods
	void initVariables();

	void initFonts();

	void initKeybinds();

	void initGUI();

	void resetGUI();

public:
    //Constructors & Destructor
    SettingsState(StateData* state_Data);

    virtual ~SettingsState();

    //Accessor Methods

    //Methods
	void updatePlayerInput(const float& delta_Time);

	void updateGUI(const float& delta_Time);

	void update(const float& delta_Time);	

	void renderGUI(sf::RenderTarget& target);

	void render(sf::RenderTarget* target = NULL);
};

