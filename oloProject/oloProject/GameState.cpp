#include "GameState.h"

void GameState::initKeybinds()
{

	std::ifstream ifs("Config/gamestateKeybinds.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->Keybinds[key] = this->SupportedKeys->at(key2);
		}
	}

	ifs.close();

	//this->Keybinds["CLOSE"] = this->SupportedKeys->at("Escape");
	//this->Keybinds["MOVE_LEFT"] = this->SupportedKeys->at("A");
	//this->Keybinds["MOVE_DOWN"] = this->SupportedKeys->at("S");
	//this->Keybinds["MOVE_RIGHT"] = this->SupportedKeys->at("D");
	//this->Keybinds["MOVE_UP"] = this->SupportedKeys->at("W");
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	: State(window, supportedKeys, statesStack)
{
	this->initKeybinds();
	this->StatesStack = statesStack;
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "ending game state" << "\n";
}

void GameState::updateKeyInput(const float& deltaTime)
{
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_LEFT"))))
		this->Entity.move(deltaTime, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_DOWN"))))
		this->Entity.move(deltaTime, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_RIGHT"))))
		this->Entity.move(deltaTime, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_UP"))))
		this->Entity.move(deltaTime, 0.f, -1.f);
}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeyInput(deltaTime);
	this->Entity.update(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	if(!target)
		target = this->Window;

	this->Entity.render(target);
}
