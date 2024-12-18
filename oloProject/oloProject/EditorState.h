#pragma once
#include "State.h"
#include"Button.h"

class EditorState :
    public State
{
private:
	//Variables
	sf::Font Font;

	std::map<std::string, Button*> Buttons;

	//Methods
	void initBackground();
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack);
	virtual ~EditorState();

	//Methods
	void updateKeyInput(const float& deltaTime);
	void updateButtons();
	void update(const float& deltaTime);

	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);

};

