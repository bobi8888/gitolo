#include "stdafx.h"

#include "SettingsState.h"

//Initializer Methods
void SettingsState::initBackground()
{
	this->Background.setSize(
		sf::Vector2f
		(
			static_cast <float>(this->Window->getSize().x),
			static_cast <float>(this->Window->getSize().y)
		)
	);

	if (!this->BackgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.png"))
	{
		throw"ERROR::MainMenuState::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->Background.setTexture(&this->BackgroundTexture);
}

void SettingsState::initVariables()
{
	this->VideoModes = sf::VideoMode::getFullscreenModes(); 
}

void SettingsState::initFonts()
{
	if (!this->Font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
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

void SettingsState::initGUI()
{
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color

	this->Buttons["BACK_BTN"] = new gui::Button(
		this->Window->getSize().x / 2.f, 500.f, 150.f, 50.f,
		&this->Font, "Back", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
		);

	this->Buttons["APPLY_BTN"] = new gui::Button(
		this->Window->getSize().x / 2.f, 600.f, 150.f, 50.f,
		&this->Font, "Apply", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	std::vector<std::string> videoModesStr;

	for (auto& i : this->VideoModes)
	{
		videoModesStr.push_back(std::to_string(i.width) + " x " + std::to_string(i.width));
	}
	//std::string li[] = {"1920x1080", "800x600", "640x480"};

	this->DropdownMap["RESOLUTION"] = new gui::DropdownList(
		this->Window->getSize().x / 2.f, 150.f, 150.f, 20.f, 
		Font, videoModesStr.data(), videoModesStr.size()
	);
}

void SettingsState::initText()
{
	this->OptionsText.setFont(this->Font);

	this->OptionsText.setPosition(sf::Vector2f(100.f, 400.f));

	this->OptionsText.setCharacterSize(30.f);

	this->OptionsText.setFillColor(sf::Color::Black);

	this->OptionsText.setString("Resolution \nFullscreen \nVsync \nAntialiasing");
}

//Constructors & Destructor
SettingsState::SettingsState(
	sf::RenderWindow* window, 
	GraphicsSettings& graphicsSettings,
	std::map<std::string, 
	int>* supportedKeys, 
	std::stack<State*>* statesStack
	) : State(window, supportedKeys, statesStack), SettingsGraphicsSettings(graphicsSettings)
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
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		delete it->second;
	}

	for (auto it2 = this->DropdownMap.begin(); it2 != this->DropdownMap.end(); ++it2)
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
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->update(this->MousePositionView);
	}

	//Button Functionality
	//Quit State
	if (this->Buttons["BACK_BTN"]->isPressed())
	{
		this->endState();
	}

	if (this->Buttons["APPLY_BTN"]->isPressed())
	{
		//for testing, remove later
		//std::cout << this-> VideoModes[this->DropdownMap["RESOLUTION"]->getActiveElementId()];

		this->SettingsGraphicsSettings.Resolution = this->VideoModes[this->DropdownMap["RESOLUTION"]->getActiveElementId()];

		this->Window->create(this->SettingsGraphicsSettings.Resolution, "Spuh", sf::Style::Default);
	}

	//DropdownList
	for (auto it = this->DropdownMap.begin(); it != this->DropdownMap.end(); ++it)
	{
		it->second->update(this->MousePositionView, deltaTime);
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
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->render(target);
	}

	for (auto it2 = this->DropdownMap.begin(); it2 != this->DropdownMap.end(); ++it2)
	{
		it2->second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;

	target->draw(this->Background);

	this->renderGUI(*target);

	target->draw(this->OptionsText);
	//this->ddl->render(*target);

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