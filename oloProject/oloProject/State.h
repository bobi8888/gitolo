#pragma once

#include "Player.h"

class State
{
private:
	
protected:
	std::stack<State*>* StatesStack;
	sf::RenderWindow* Window;
	std::map<std::string, int>* SupportedKeys;
	std::map<std::string, int> Keybinds;
	bool Quit;
	bool IsPaused; 

	sf::Vector2i MousePositionScreen;
	sf::Vector2i MousePositionWindow;
	sf::Vector2f MousePositionView;

	//Resources
	std::map<std::string, sf::Texture> TexturesMap;

	//Methods
	virtual void initKeybinds() = 0;

public:
	//Constructors/Destructors
	State();
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* StatesStack);
	virtual ~State();

	//Methods
	const bool& getQuit() const;
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updatePlayerInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
