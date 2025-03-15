#include "stdafx.h"

#include "EditorState.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> v{ 3, 1, -14, 1, 5, 9, -14, 9 };
std::vector<int>::iterator result = std::max_element(v.begin(), v.end());

//Initializer Methods
void EditorState::initRender()
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

void EditorState::initVariables()
{
	this->tileToolTextureRect = sf::IntRect(0, 0, static_cast<int> (this->stateData->gridSize), static_cast<int> (this->stateData->gridSize));

	this->collision = false;

	this->type = TileTypes::DEFAULT;

	this->cameraSpeed = 750.f;

	this->layer = 0;

	this->tileAddLock = false;
	
	this->renderState = new sf::RenderStates();
	this->lightShader = new sf::Shader();

	//this->renderState->shader = this->lightShader;
	this->renderState->shader = &particleShader;

	this->renderState->blendMode = sf::BlendAdd;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	this->particleBurst = new ParticleBurst(300, 45, 135);
	this->particleBurst->setPosition(300.f, 300.f);

	this->particleTrickle = new ParticleTrickle(
		"dust.png",3, 
		10.f, 25,
		160.f, 200.f,
		sf::seconds(0.5f), sf::seconds(1.f)
	);

	this->particleTrickle->setPosition(400.f, 400.f);


//make notes on this
//this->stateWindow->draw(*this->vertexBuffer, &this->lightShader);

//make notes on this
//this->stateWindow->draw(*vertexBuffer, states);
	//try using vetex buffer ?
		//Create vertices of the triagle
		std::vector<sf::Vertex> vertices = {
				sf::Vertex(sf::Vector2f(100.f, 100.f), sf::Color::Red),
				sf::Vertex(sf::Vector2f(150.f, 50.f),  sf::Color::Red),
				sf::Vertex(sf::Vector2f(200.f, 100.f), sf::Color::Red)
		};

		//set the VertexBuffer 
		this->vertexBuffer = new sf::VertexBuffer(sf::Triangles, sf::VertexBuffer::Usage::Static);
		this->vertexBuffer->create(vertices.size());
		this->vertexBuffer->update(&vertices[0]);

		//sets the shape of the shader?
		sf::Glsl::Vec3 vec;
		vec.x = 100.f;
		vec.x = 200.f;
		vec.x = 300.f;

		//if (!this->lightShader->loadFromFile("light_shader.frag", sf::Shader::Fragment))
		//{
		//	std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
		//}		
		//else
		//{
		//	std::cout << "SHADER LOADED CORRECTLY" << "\n";
		//}
		//this->lightShader->setUniform("windowHeight", static_cast<float>(this->stateWindow->getSize().y));

		if (particleShader.loadFromFile("dust_particle_shader.frag", sf::Shader::Fragment))
		{
			std::cout << "ERROR::GAMESTATE::COULD NOT LOAD DUST_PARTICLE_SHADER.FRAG" << "\n";
		}
		else
		{
			std::cout << "DUST PARTICLE SHADER LOADED CORRECTLY" << "\n";
		}
}

void EditorState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->graphicsSettings->Resolution.width), 
			static_cast<float>(this->stateData->graphicsSettings->Resolution.height)
		));

	this->view.setCenter(
		this->stateData->graphicsSettings->Resolution.width / 2.f,
		this->stateData->graphicsSettings->Resolution.height / 2.f
	);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
	{
		throw("ERROR::EditorState::Could not load font.");
	}
}

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(18);
}

void EditorState::initKeybinds()
{

	std::ifstream ifs("Config/editorStateKeybinds.txt");

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

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(this->stateData->graphicsSettings->Resolution, this->font);

	const sf::VideoMode& videoMode = this->stateData->graphicsSettings->Resolution;

	this->pauseMenu->addButton(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(35.f, videoMode),
		gui::convertToPixelsX(20.f, videoMode), gui::convertToPixelsY(5.f, videoMode),
		"SAVE",	"Save Texture Map", gui::calculateCharSize(videoMode, 75)
	);

	this->pauseMenu->addButton(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(45.f, videoMode),
		gui::convertToPixelsX(20.f, videoMode), gui::convertToPixelsY(5.f, videoMode),
		"LOAD",	"Load Texture Map", gui::calculateCharSize(videoMode, 75)
	);

	this->pauseMenu->addButton(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(65.f, videoMode),
		gui::convertToPixelsX(20.f, videoMode), gui::convertToPixelsY(5.f, videoMode),
		"QUIT", "Quit Game", gui::calculateCharSize(videoMode, 75)
	);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(
		this->stateData->gridSize, 
		25, 25, 
		//this->tileToolTextureRect, 
		"Resources/Images/Tiles/tiles50.png"

	);
}

void EditorState::initGui()
{
	this->tileToolSelectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->tileToolSelectorRect.setFillColor(sf::Color(255, 255, 255, 150));

	this->tileToolSelectorRect.setOutlineThickness(1.f);

	this->tileToolSelectorRect.setOutlineColor(sf::Color::White);

	this->tileToolSelectorRect.setTexture(this->tileMap->getTileTextureSheet());

	this->tileToolSelectorRect.setTextureRect(this->tileToolTextureRect);

	this->textureSelector = new gui::TextureSelector(
		76.f, 30.f,
		450.f, 350.f,
		this->stateData->gridSize,
		this->tileMap->getTileTextureSheet(),
		this->font, "Show/Hide"
	);

	this->sideBar.setSize(
		sf::Vector2f(
			75.f,
			static_cast<float>(this->stateData->graphicsSettings->Resolution.height)
		)
	);
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sideBar.setOutlineThickness(2.f);
}

//Constructors & destructor
EditorState::EditorState(StateData* stateData) 
	: State(stateData)
{
	this->initRender(); 
	this->initVariables();
	this->initView();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initTileMap();
	this->initGui();

	this->keytimeMax = 3.f;
	//DEBUG
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pauseMenu;

	delete this->tileMap;

	delete this->textureSelector;
}

//Methods
//Update Methods
void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pauseMenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("editorTileMap.txt");

	if (this->pauseMenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("editorTileMap.txt");
}

void EditorState::updatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->isPaused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateButtons()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePositionWindow);
	}
}

void EditorState::updateGUI(const float& deltaTime)
{
	this->textureSelector->update(this->mousePositionWindow, deltaTime);

	if (!this->textureSelector->getIsActive())
	{
		this->tileToolSelectorRect.setPosition(
			this->mousePositionGrid.x * this->stateData->gridSize,
			this->mousePositionGrid.y * this->stateData->gridSize
		);
	}

	this->cursorText.setPosition(sf::Vector2f(this->mousePositionView.x, this->mousePositionView.y + 15.f));

	std::stringstream ss;

	ss << this->mousePositionView.x << "  " << this->mousePositionView.y << "\n" <<
		this->mousePositionGrid.x << "  " << this->mousePositionGrid.y << "\n" <<
		this->tileToolTextureRect.left << " " << this->tileToolTextureRect.top << "\n" <<
		"Collision:" << this->collision << "\n" <<
		"Type: " << this->type << "\n" <<
		"# of Tiles: " << this->tileMap->getLayerSize(this->mousePositionGrid, this->layer) << "\n" << 
		"TileLock: " << this->tileAddLock;

	this->cursorText.setString(ss.str());
}

void EditorState::updateEditorInput(const float& deltaTime)
{
	//Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -std::floor(this->cameraSpeed * deltaTime));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, std::floor(this->cameraSpeed * deltaTime));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-std::floor(this->cameraSpeed * deltaTime), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(std::floor(this->cameraSpeed * deltaTime), 0.f);
	}

	//Adding a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePositionWindow)))
		{
			if (!this->textureSelector->getIsActive())
			{
				if (
					(this->tileMap->getLayerSize(this->mousePositionGrid, this->layer) < 1 && this->tileAddLock) 
					|| !this->tileAddLock
					)
				{
					this->tileMap->addTile(
						this->mousePositionGrid.x, this->mousePositionGrid.y, 0,
						this->tileToolTextureRect,
						this->collision, this->type
					);
				}
			}
			else
			{
				this->tileToolTextureRect = this->textureSelector->getTextureRect();

				this->tileToolSelectorRect.setTextureRect(this->tileToolTextureRect);
			}
		}
	}

	//Removing a tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePositionWindow)))
		{
			if (!this->textureSelector->getIsActive())
			{
				this->tileMap->removeTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0);
			}
		}
	}

	//Toggle Collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeyTime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	//Toggle Type
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCREASE_TYPE"))) && this->getKeyTime())
	{
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECREASE_TYPE"))) && this->getKeyTime())
	{
		if (this->type > 0)
			--this->type;
	}
	//Toggle TileAddLock
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TILEADDLOCK"))) && this->getKeyTime())
	{
		if(this->tileAddLock) 
			this->tileAddLock = false; 
		else 
			this->tileAddLock = true;
	}
}

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions(&this->view);

	this->updateKeytime(deltaTime);

	this->updatePlayerInput(deltaTime);

	if (!this->isPaused)
	{
		this->updateGUI(deltaTime);

		this->updateButtons();

		this->updateEditorInput(deltaTime);
	}
	else
	{
		this->pauseMenu->update(this->mousePositionWindow);

		this->updatePauseMenuButtons();
	}	

	sf::Time elapsed = clock.restart();
	this->particleBurst->update(elapsed);
	this->particleTrickle->update(elapsed);

	particleShader.setUniform("time", clock.getElapsedTime().asSeconds());

}

//Render Methods
void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	if (!this->textureSelector->getIsActive())
	{
		target.setView(this->view);

		target.draw(this->tileToolSelectorRect);
	}

	target.setView(this->stateWindow->getDefaultView());

	this->textureSelector->render(target);

	target.draw(this->sideBar);

	target.setView(this->view);

	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->stateWindow;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture,
		this->mousePositionGrid, 
		*this->lightShader,
		*this->renderState, 
		this->mousePositionWindowFloat,
		true
	);

	this->tileMap->renderDeferred(
		this->renderTexture,
		*this->lightShader,
		*this->renderState,
		this->mousePositionWindowFloat
	);

	if (this->isPaused)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());

		this->pauseMenu->render(this->renderTexture);
	}

	//Final Render
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());

	target->draw(this->renderSprite);

	this->renderGUI(*target);

	target->draw(*particleBurst, *this->renderState);
	target->draw(*particleTrickle, *this->renderState);
}