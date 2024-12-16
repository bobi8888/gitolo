#pragma once

#include"GameState.h"
#include"Button.h"

class MainMenuState :
    public State
{
private:
	//Variables
	sf::Texture BackgroundTexture;
	sf::RectangleShape Background;
	sf::Font Font;

	std::map<std::string, Button*> Buttons;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack);
	virtual ~MainMenuState();

	//Methods
	void updateKeyInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);

};

