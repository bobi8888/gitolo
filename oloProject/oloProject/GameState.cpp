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

void GameState::initFonts()
{
	if (!this->Font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
	{
		throw("ERROR::MainMenuState::Could not load font.");
	}
}
void GameState::initTextures()
{
	if (!this->TexturesMap["SKIRT_SHEET"].loadFromFile("Resources/Images/Sprites/Skirt/SKIRT_SHEET.png"))

		throw("ERROR::GameState::COULD_NOT_LOAD_PLAYER_TEXTURE");
}

void GameState::initPlayers()
{
	this->GameStatePlayer = new Player(this->TexturesMap["SKIRT_SHEET"], 0, 0);
}

//Constructors & Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	: State(window, supportedKeys, statesStack), PauseMenu(*window, Font)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->GameStatePlayer;
}

void GameState::updatePausedInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))))
	{
		if (!this->IsPaused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_LEFT"))))
		this->GameStatePlayer->move(-1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_DOWN"))))
		this->GameStatePlayer->move(0.f, 1.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_RIGHT"))))
		this->GameStatePlayer->move(1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("MOVE_UP"))))
		this->GameStatePlayer->move(0.f, -1.f, deltaTime);
	

}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updatePausedInput(deltaTime);

	if (!this->IsPaused)
	{
		this->updatePlayerInput(deltaTime);
		this->GameStatePlayer->update(deltaTime);
	}
	else
	{
		this->PauseMenu.update();
	}
}

void GameState::render(sf::RenderTarget* target)
{	
	if(!target)
		target = this->Window;

	this->GameStatePlayer->render(*target);

	if (this->IsPaused)
		this->PauseMenu.render(*target);
	
}
