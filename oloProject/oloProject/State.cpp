#include "State.h"

State::State(){}

State::State(sf::RenderWindow* window)
{
	this->Window = window;
	this->Quit = false;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->Quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->Quit = true;
	}
}
