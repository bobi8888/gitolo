#include "stdafx.h"

#include "State.h"

//Constructors/Destructors
//State::State(){}

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->stateWindow = stateData->stateDataWindow;
	this->supportedKeys = stateData->supportedKeys;
	this->statesStack = stateData->statesStack;
	this->quit = false;
	this->isPaused = false;
	this->keytime = 0.f;
	this->keytimeMax = 3.f;
	this->gridSize = stateData->gridSize;

	this->testWindow = new sf::RenderWindow();
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
	//this->mousePositionScreen = sf::Mouse::getPosition();

	this->mousePositionWindowFloat = sf::Vector2f(
		static_cast<float>(sf::Mouse::getPosition(*this->stateWindow).x),
		static_cast<float>(sf::Mouse::getPosition(*this->stateWindow).y)
	);

	this->mousePositionWindow = sf::Mouse::getPosition(*this->stateWindow);

	if (view)
		this->stateWindow->setView(*view);
	
	this->mousePositionView = this->stateWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->stateWindow));
	this->mousePositionGrid = 
		sf::Vector2i(
			static_cast<int>(this->mousePositionView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePositionView.y) / static_cast<int>(this->gridSize)
		);

	//this shouldn't be here
	this->stateWindow->setView(this->stateWindow->getDefaultView());
}

void State::updateKeytime(const float& deltaTime)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * deltaTime;
}
