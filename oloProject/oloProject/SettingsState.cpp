#include "stdafx.h"

#include "SettingsState.h"

//Initializer Methods
void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast <float>(this->window->getSize().x),
			static_cast <float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.png"))
	{
		throw"ERROR::MainMenuState::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes(); 
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
	{
		throw("ERROR::MainMenuState::Could not load font.");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainMenuStateKeybinds.txt");

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

void SettingsState::initGUI()
{
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color

	this->buttons["BACK_BTN"] = new gui::Button(
		this->window->getSize().x / 2.f, 500.f, 150.f, 50.f,
		&this->font, "Back", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
		);

	this->buttons["APPLY_BTN"] = new gui::Button(
		this->window->getSize().x / 2.f, 600.f, 150.f, 50.f,
		&this->font, "Apply", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	std::vector<std::string> videoModesStr;

	for (auto& i : this->videoModes)
	{
		videoModesStr.push_back(std::to_string(i.width) + " x " + std::to_string(i.width));
	}
	//std::string li[] = {"1920x1080", "800x600", "640x480"};

	this->dropdownMap["RESOLUTION"] = new gui::DropdownList(
		this->window->getSize().x / 2.f, 150.f, 150.f, 20.f, 
		font, videoModesStr.data(), videoModesStr.size()
	);
}

void SettingsState::initText()
{
	this->text.setFont(this->font);

	this->text.setPosition(sf::Vector2f(100.f, 400.f));

	this->text.setCharacterSize(30.f);

	this->text.setFillColor(sf::Color::Black);

	this->text.setString("Resolution \nFullscreen \nVsync \nAntialiasing");
}

//Constructors & Destructor
SettingsState::SettingsState(StateData* stateData) 
	: State(stateData)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initGUI();
	this->initKeybinds();
	this->initText();
}

SettingsState::~SettingsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	for (auto it2 = this->dropdownMap.begin(); it2 != this->dropdownMap.end(); ++it2)
	{
		delete it2->second;
	}
}

//Update Methods
void SettingsState::updatePlayerInput(const float& deltaTime)
{

}

void SettingsState::updateGUI(const float& deltaTime)
{
	//Updates all the GUI elements in the state and handle their functionality
	//Buttons
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePositionWindow);
	}

	//Button Functionality
	//Quit State
	if (this->buttons["BACK_BTN"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY_BTN"]->isPressed())
	{
		//for testing, remove later
		//std::cout << this-> VideoModes[this->DropdownMap["RESOLUTION"]->getActiveElementId()];

		this->stateData->graphicsSettings->Resolution = this->videoModes[this->dropdownMap["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->graphicsSettings->Resolution, "Spuh", sf::Style::Default);
	}

	//DropdownList
	for (auto it = this->dropdownMap.begin(); it != this->dropdownMap.end(); ++it)
	{
		it->second->update(this->mousePositionWindow, deltaTime);
	}

	//DropdownList Functionality
}

void SettingsState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updatePlayerInput(deltaTime);
	this->updateGUI(deltaTime);

	//this->ddl->update(this->MousePositionView, deltaTime);
	//DEBUG
	//system("cls");
	//std::cout << this->MousePositionView.x << " " << this->MousePositionView.y;
}

//Render Methods
void SettingsState::renderGUI(sf::RenderTarget& target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->render(target);
	}

	for (auto it2 = this->dropdownMap.begin(); it2 != this->dropdownMap.end(); ++it2)
	{
		it2->second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGUI(*target);

	target->draw(this->text);
	//this->ddl->render(*target);

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