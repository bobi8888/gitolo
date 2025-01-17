#include "stdafx.h"

#include "GameState.h"

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			this->stateData->graphicsSettings->Resolution.width,
			this->stateData->graphicsSettings->Resolution.height
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->graphicsSettings->Resolution.width / 2.f,
			this->stateData->graphicsSettings->Resolution.height / 2.f
		)
	);
}

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
			this->keybinds[key] = this->supportedKeys->at(key2);
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
	if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
	{
		throw("ERROR::MainMenuState::Could not load font.");
	}
}

void GameState::initTextures()
{
	if (!this->texturesMap["SKIRT_SHEET"].loadFromFile("Resources/Images/Sprites/Skirt/SKIRT_SHEET.png"))

		throw("ERROR::GameState::COULD_NOT_LOAD_PLAYER_TEXTURE");
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton(
		"QUIT", 
		"Quit Game",
		this->pauseMenu->getContainer().getPosition().x, 
		this->pauseMenu->getContainer().getPosition().y + 200.f		
	);
}

void GameState::initPlayers()
{
	this->player = new Player(this->texturesMap["SKIRT_SHEET"], 0, 0);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, this->texture_rect, "Resources/Images/Tiles/quadTexture.png");

	this->tileMap->loadFromFile("editorTileMap.txt");
}

//Constructors & Destructors
GameState::GameState(StateData* stateData)
	: State(stateData)
{
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;

	delete this->pauseMenu;

	delete this->tileMap;
}

//Methods
void GameState::updateView(const float& deltaTime)
{
	this->view.setCenter(this->player->getPosition());
}
void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->isPaused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, deltaTime);
	

}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(deltaTime);
	this->updateInput(deltaTime);

	if (!this->isPaused)
	{
		this->updateView(deltaTime);

		this->updatePlayerInput(deltaTime);

		this->player->update(deltaTime);
	}
	else
	{
		this->pauseMenu->update(this->mousePositionWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{	
	if(!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target);

	this->player->render(*target);

	if (this->isPaused)
	{
		target->setView(this->window->getDefaultView());

		this->pauseMenu->render(*target);
	}

	//Debugging
	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(this->mousePositionView.x, this->mousePositionView.y + 15));
	mouse_text.setFont(this->font);
	mouse_text.setCharacterSize(18);
	std::stringstream ss;
	ss << this->mousePositionView.x << "  " << this->mousePositionView.y;
	mouse_text.setString(ss.str());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		target->draw(mouse_text);
	
}
