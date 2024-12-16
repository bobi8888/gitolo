#include "State.h"

State::State(){}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
{
	this->Window = window;
	this->SupportedKeys = supportedKeys;
	this->StatesStack = statesStack;
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

void State::updateMousePositions()
{
	this->MousePositionScreen = sf::Mouse::getPosition();
	this->MousePositionWindow = sf::Mouse::getPosition(*this->Window);
	this->MousePositionView = this->Window->mapPixelToCoords(sf::Mouse::getPosition(*this->Window));
}
