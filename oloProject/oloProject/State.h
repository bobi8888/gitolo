#pragma once

#include "Entity.h"

class State
{
private:

protected:
	sf::RenderWindow* Window;
	std::map<std::string, int>* SupportedKeys;
	std::map<std::string, int> Keybinds;
	bool Quit = false;

	//Resources
	std::vector<sf::Texture> Textures;

	//Methods
	virtual void initKeybinds() = 0;

public:
	//Constructors/Destructors
	State();
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	//Methods
	const bool& getQuit() const;
	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void updateKeyInput(const float& deltaTime) = 0;
	//virtual void endState() = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
