#include "stdafx.h"

#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->graphicsSettings->Resolution.width,
		this->stateData->graphicsSettings->Resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0, 
			this->stateData->graphicsSettings->Resolution.width, 
			this->stateData->graphicsSettings->Resolution.height
		)
	);

}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f( 
			static_cast<float>(this->stateData->graphicsSettings->Resolution.width),
			static_cast<float>(this->stateData->graphicsSettings->Resolution.height)
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
	if (!this->texturesMap["ROBO_100"].loadFromFile(
		"Resources/Images/Sprites/Robo/ROBO_100.png"
		)
	)
	
	throw("ERROR::GameState::COULD_NOT_LOAD_PLAYER_TEXTURE");
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(this->stateData->graphicsSettings->Resolution, this->font);

	const sf::VideoMode& videoMode = this->stateData->graphicsSettings->Resolution;

	this->pauseMenu->addButton(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(50.f, videoMode),
		gui::convertToPixelsX(12.f, videoMode), gui::convertToPixelsY(5.f, videoMode),
		"QUIT", "Quit Game", gui::calculateCharSize(videoMode, 75)
		);
}

void GameState::initShaders()
{
	if (!this->mainShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(this->texturesMap["ROBO_100"], 0, 0);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->graphicsSettings->Resolution);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(
		this->stateData->gridSize, 
		1000, 1000, 
		this->texture_rect, 
		"Resources/Images/Tiles/tiles50.png"
	);

	this->tileMap->loadFromFile("editorTileMap.txt");
}

//Constructors & Destructors
GameState::GameState(StateData* stateData)
	: State(stateData)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();
	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();

	//DEBUG
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(18);
}

GameState::~GameState()
{
	delete this->player;

	delete this->playerGUI;

	delete this->pauseMenu;

	delete this->tileMap;
}

//Methods
void GameState::updateView(const float& deltaTime)
{
	//std::floor helps with screen tearing because using float values makes it hard to be pixel perfect
	//look into this for a better explaination

	this->view.setCenter(
		//move camera with player movement
		std::floor(this->player->getHitboxPosition().x 
			//move camera with mouse movement
			+ (static_cast<float>(this->mousePositionWindow.x) 
			- static_cast<float>(this->stateData->graphicsSettings->Resolution.width / 2)) / 5.f),
		//move camera with player movement
		std::floor(this->player->getHitboxPosition().y 
			//move camera with mouse movement
			+ (static_cast<float>(this->mousePositionWindow.y)
			- static_cast<float>(this->stateData->graphicsSettings->Resolution.height / 2)) / 5.f)
	);
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

//void GameState::updatePlayerGUI(const float& deltaTime)
//{
//	//this->playerGUI->update(deltaTime, this->view.getCenter());
//	//this->playerGUI->update(deltaTime, this->player->getSpritePosition());
//}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& deltaTime)
{
	this->tileMap->updateCollision(this->player, deltaTime);
}

void GameState::update(const float& deltaTime)
{
	this->updateMousePositions(&this->view);

	this->updateKeytime(deltaTime);

	this->updateInput(deltaTime);

	//DEBUG
	this->cursorText.setPosition(
		sf::Vector2f(
			static_cast<float>(this->mousePositionWindow.x), 
			static_cast<float>(this->mousePositionWindow.y) + 15.f
		)
	);

	std::stringstream ss;

	ss << this->mousePositionView.x << "  " << this->mousePositionView.y << "\n";

	this->cursorText.setString(ss.str());
	//DEBUG

	if (!this->isPaused)
	{
		this->updateView(deltaTime);

		this->updatePlayerInput(deltaTime);

		this->updateTileMap(deltaTime);

		this->player->update(deltaTime);

		this->playerGUI->update(deltaTime);
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

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture, 
		this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)),
		&this->mainShader,
		this->player->getSpriteCenter(),
		false
		);

	this->player->render(this->renderTexture, &this->mainShader);

	this->tileMap->renderDeferred(
		this->renderTexture, 
		&this->mainShader, 
		this->player->getSpriteCenter()
	);

	this->playerGUI->render(this->renderTexture);

	this->renderTexture.setView(this->renderTexture.getDefaultView());


	if (this->isPaused)
	{
		this->pauseMenu->render(this->renderTexture);
	}

	//Final Render
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());

	target->draw(this->renderSprite);
		
	//Debugging
	//sf::Text mouse_text;
	//mouse_text.setPosition(sf::Vector2f(this->mousePositionView.x, this->mousePositionView.y + 15));
	//mouse_text.setFont(this->font);
	//mouse_text.setCharacterSize(18);
	//std::stringstream ss;
	//ss << this->mousePositionView.x << "  " << this->mousePositionView.y;
	//mouse_text.setString(ss.str());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		//target->draw(mouse_text);

		target->draw(this->cursorText);
	}
	
}
