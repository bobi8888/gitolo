#include "stdafx.h"

#include "SettingsState.h"

//Initializer Methods
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
	const sf::VideoMode& videoMode = this->stateData->graphicsSettings->Resolution;

	//Init Background
	this->background.setSize(
		sf::Vector2f(
			static_cast <float>(videoMode.width),
			static_cast <float>(videoMode.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/background.png"))
	{
		throw"ERROR::MainMenuState::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Init Buttons	
	
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color
	this->buttons["APPLY_BTN"] = new gui::Button(
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(35.f, videoMode),
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(6.f, videoMode),
		&this->font, "Apply", gui::calculateCharSize(videoMode),
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	this->buttons["BACK_BTN"] = new gui::Button(
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(45.f, videoMode), 
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(6.f, videoMode),
		&this->font, "Back", gui::calculateCharSize(videoMode),
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	//Init Resolution Dropdown List
	std::vector<std::string> videoModesStr;

	for (auto& i : this->videoModes)
	{
		videoModesStr.push_back(std::to_string(i.width) + " x " + std::to_string(i.height));
	}

	this->dropdownMap["RESOLUTION"] = new gui::DropdownList(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(5.f, videoMode),
		gui::convertToPixelsX(12.f, videoMode), gui::convertToPixelsY(3.5f, videoMode),
		//font, videoModesStr.data(), gui::calculateCharSize(videoMode, 110),
		font, videoModesStr, gui::calculateCharSize(videoMode, 110),
		static_cast<int>(videoModesStr.size()), valid_Resolutions
	);

	//Init Text
	this->text.setFont(this->font);

	this->text.setPosition(
		sf::Vector2f(
			gui::convertToPixelsX(5.f, videoMode),
			gui::convertToPixelsY(5.f, videoMode)
		)
	);

	this->text.setCharacterSize(gui::calculateCharSize(videoMode));

	this->text.setFillColor(sf::Color::Black);

	this->text.setString(
		"Resolution: "
		+ std::to_string(this->stateData->graphicsSettings->Resolution.width)
		+ " x "
		+ std::to_string(this->stateData->graphicsSettings->Resolution.height) + "\n"
		+ "Fullscreen \nVsync \nAntialiasing"
	);
}

void SettingsState::resetGUI()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

	this->buttons.clear();

	for (auto it2 = this->dropdownMap.begin(); it2 != this->dropdownMap.end(); it2++)
	{
		delete it2->second;
	}

	this->dropdownMap.clear();

	this->initGUI();
}

//Constructors & Destructor
SettingsState::SettingsState(StateData* state_Data) 
	: State(state_Data)
{
	this->initVariables();

	this->initFonts();

	this->initGUI();

	this->initKeybinds();
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
void SettingsState::updatePlayerInput(const float& delta_Time)
{

}

void SettingsState::updateGUI(const float& delta_Time)
{
	//Buttons
		for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePositionWindow);
	}

	//Quit State
	if (this->buttons["BACK_BTN"]->isPressed())
	{
		this->endState();
	}
	
	//Apply New Resolution
	if (this->buttons["APPLY_BTN"]->isPressed() && dropdownMap["RESOLUTION"]->getActiveElementId() != 0)
	{		 
		this->stateData->graphicsSettings->Resolution = this->videoModes[this->dropdownMap["RESOLUTION"]->getActiveElementId()];

		this->window->create(
			this->stateData->graphicsSettings->Resolution,
			this->stateData->graphicsSettings->Title,
			sf::Style::Default
		);

		this->resetGUI();		
	}

	//DropdownList
	for (auto it = this->dropdownMap.begin(); it != this->dropdownMap.end(); ++it)
	{
		it->second->update(this->mousePositionWindow, delta_Time);
	}

	this->text.setString(
		"Resolution: "
		+ std::to_string(this->stateData->graphicsSettings->Resolution.width)
		+ " x "
		+ std::to_string(this->stateData->graphicsSettings->Resolution.height) + "\n"
		+ "Fullscreen \nVsync \nAntialiasing");
}

void SettingsState::update(const float& delta_Time)
{
	this->updateMousePositions();

	this->updateGUI(delta_Time);
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