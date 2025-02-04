#include "stdafx.h"

#include "State.h"

//Constructors/Destructors
State::State(){}

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->statesStack = stateData->statesStack;
	this->quit = false;
	this->isPaused = false;
	this->keytime = 0.f;
	this->keytimeMax = 3.f;
	this->gridSize = stateData->gridSize;
}

State::~State()
{
}

//Accessor Methods
const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//Methods
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->isPaused = true;
}

void State::unpauseState()
{
	this->isPaused = false;
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);
	
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePositionGrid = 
		sf::Vector2i(
			static_cast<int>(this->mousePositionView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePositionView.y) / static_cast<int>(this->gridSize)
		);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& deltaTime)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * deltaTime;
}
