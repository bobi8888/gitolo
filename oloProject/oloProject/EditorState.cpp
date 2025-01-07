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

	//DEBUG
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pauseMenu;
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

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeytime(deltaTime);
	this->updatePlayerInput(deltaTime);

	if (!this->isPaused)
	{
		this->updateButtons();
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

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(*target);

	this->tileMap.render(*target);

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