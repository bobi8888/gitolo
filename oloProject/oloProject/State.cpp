#include "State.h"

State::State(){}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->Window = window;
	this->SupportedKeys = supportedKeys;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE")))) {
		this->Quit = true;
	}
}
