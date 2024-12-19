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
	if (!this->Font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
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
			this->Keybinds[key] = this->SupportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::initButtons()
{

}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	: State(window, supportedKeys, statesStack)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
	this->initKeybinds();

	//DEBUG
}

EditorState::~EditorState()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::updatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->update(this->MousePositionView);
	}
}

void EditorState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updatePlayerInput(deltaTime);
	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;

	this->renderButtons(*target);

	//Debugging
	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(this->MousePositionView.x, this->MousePositionView.y + 15));
	mouse_text.setFont(this->Font);
	mouse_text.setCharacterSize(18);
	std::stringstream ss;
	ss << this->MousePositionView.x << " " << this->MousePositionView.y;
	mouse_text.setString(ss.str());
	target->draw(mouse_text);
}