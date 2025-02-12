#pragma once

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	//StateData(){};

	//Variables
	float gridSize;

	sf::RenderWindow* window; 

	GraphicsSettings* graphicsSettings;

	std::map<std::string, int>* supportedKeys;

	std::stack<State*>* statesStack;
};

class State
{
private:
	
protected:
	StateData* stateData;
	std::stack<State*>* statesStack;

	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	bool quit;
	bool isPaused; 

	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2i mousePositionGrid;

	//Resources
	std::map<std::string, sf::Texture> texturesMap;

	//Methods
	virtual void initKeybinds() = 0;

public:
	//Constructors/Destructors
	//State();

	State(StateData* stateData);

	virtual ~State();

	//Accessor Methods
	const bool& getQuit() const;

	const bool getKeyTime();

	//Methods
	const float convertToPixelsX(const float percent);

	const float convertToPixelsY(const float percent);

	void endState();

	void pauseState();

	void unpauseState();

	virtual void updateMousePositions(sf::View* view = nullptr);

	virtual void updateKeytime(const float& deltaTime);

	virtual void updatePlayerInput(const float& deltaTime) = 0;

	virtual void update(const float& deltaTime) = 0;
	
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
