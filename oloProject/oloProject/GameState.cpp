#include "stdafx.h"

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

void GameState::initPauseMenu()
{
	this->GameStatePauseMenu = new PauseMenu(*this->Window, this->Font);

	this->GameStatePauseMenu->addButton(
		"QUIT", 
		"Quit Game",
		this->GameStatePauseMenu->getContainer().getPosition().x, 
		this->GameStatePauseMenu->getContainer().getPosition().y + 200.f		
	);
}

void GameState::initPlayers()
{
	this->GameStatePlayer = new Player(this->TexturesMap["SKIRT_SHEET"], 0, 0);
}

//Constructors & Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	: State(window, supportedKeys, statesStack)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->GameStatePlayer;
	delete this->GameStatePauseMenu;
}

//Methods
void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->IsPaused)
			this->pauseState();
		else
			this->unpauseState();
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

void GameState::updatePauseMenuButtons()
{
	if (this->GameStatePauseMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeytime(deltaTime);
	this->updateInput(deltaTime);

	if (!this->IsPaused)
	{
		this->updatePlayerInput(deltaTime);
		this->GameStatePlayer->update(deltaTime);
	}
	else
	{
		this->GameStatePauseMenu->update(this->MousePositionView);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{	
	if(!target)
		target = this->Window;

	this->TileMap.render(*target);

	this->GameStatePlayer->render(*target);

	if (this->IsPaused)
		this->GameStatePauseMenu->render(*target);

	//Debugging
	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(this->MousePositionView.x, this->MousePositionView.y + 15));
	mouse_text.setFont(this->Font);
	mouse_text.setCharacterSize(18);
	std::stringstream ss;
	ss << this->MousePositionView.x << "  " << this->MousePositionView.y;
	mouse_text.setString(ss.str());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		target->draw(mouse_text);
	
}
