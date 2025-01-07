#include "stdafx.h"

#include "EditorState.h"

//Initializer Methods
void EditorState::initBackground()
{

}

void EditorState::initVariables()
{
	//this->BackgroundTexture;
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
	{
		throw("ERROR::EditorState::Could not load font.");
	}
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

void EditorState::initButtons()
{

}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton(
		"QUIT",
		"Quit Game",
		this->pauseMenu->getContainer().getPosition().x,
		this->pauseMenu->getContainer().getPosition().y + 200.f
	);
}

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color::Transparent);

	this->selectorRect.setOutlineThickness(1.f);

	this->selectorRect.setOutlineColor(sf::Color::White);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

//Constructors & destructor
EditorState::EditorState(StateData* stateData) 
	: State(stateData)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initGui();
	this->initTileMap();

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
}
//Methods

//Update Methods

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
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
		it->second->update(this->mousePositionView);
	}
}

void EditorState::updateGUI()
{
	this->selectorRect.setPosition(
		this->mousePositionGrid.x * this->stateData->gridSize, 
		this->mousePositionGrid.y * this->stateData->gridSize
	);
}

void EditorState::updateEditorInput(const float& deltaTime)
{
	//add a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		this->tileMap->addTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0);
	}
}

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeytime(deltaTime);
	this->updatePlayerInput(deltaTime);

	if (!this->isPaused)
	{
		this->updateGUI();
		this->updateButtons();
		this->updateEditorInput(deltaTime);
	}
	else
	{
		this->pauseMenu->update(this->mousePositionView);
		this->updatePauseMenuButtons();
	}
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
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(*target);

	this->tileMap->render(*target);

	this->renderGUI(*target);

	if (this->isPaused)
		this->pauseMenu->render(*target);

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