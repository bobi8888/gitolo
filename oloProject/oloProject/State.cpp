#include "stdafx.h"

#include "State.h"

//Constructors/Destructors
State::State(){}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
{
	this->Window = window;
	this->SupportedKeys = supportedKeys;
	this->StatesStack = statesStack;
	this->Quit = false;
	this->IsPaused = false;
	this->Keytime = 0.f;
	this->KeytimeMax = 3.f;
}

State::~State()
{
}

//Accessor Methods
const bool& State::getQuit() const
{
	return this->Quit;
}

const bool State::getKeyTime()
{
	if (this->Keytime >= this->KeytimeMax)
	{
		this->Keytime = 0.f;
		return true;
	}

	return false;
}

//Methods
void State::endState()
{
	this->Quit = true;
}

void State::pauseState()
{
	this->IsPaused = true;
}

void State::unpauseState()
{
	this->IsPaused = false;
}

void State::updateMousePositions()
{
	this->MousePositionScreen = sf::Mouse::getPosition();
	this->MousePositionWindow = sf::Mouse::getPosition(*this->Window);
	this->MousePositionView = this->Window->mapPixelToCoords(sf::Mouse::getPosition(*this->Window));
}

void State::updateKeytime(const float& deltaTime)
{
	if (this->Keytime < this->KeytimeMax)
		this->Keytime += 10.f * deltaTime;
}
