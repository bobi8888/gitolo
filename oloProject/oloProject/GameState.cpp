#include "GameState.h"

//Initializer Methods
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

void GameState::initTextures()
{
	if (!this->TexturesMap["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Fish/fish.png"))
		throw("ERROR::GameState::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE");
}

void GameState::initPlayers()
{
	this->GameStatePlayer = new Player(this->TexturesMap["PLAYER_IDLE"], 0, 0);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	: State(window, supportedKeys, statesStack)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	//this->StatesStack = statesStack;
}

GameState::~GameState()
{
	delete this->GameStatePlayer;
}

void GameState::updateKeyInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_LEFT"))))
		this->GameStatePlayer->move(-1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_DOWN"))))
		this->GameStatePlayer->move(0.f, 1.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_RIGHT"))))
		this->GameStatePlayer->move(1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_UP"))))
		this->GameStatePlayer->move(0.f, -1.f, deltaTime);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeyInput(deltaTime);
	this->GameStatePlayer->update(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	if(!target)
		target = this->Window;

	this->GameStatePlayer->render(target);
}
