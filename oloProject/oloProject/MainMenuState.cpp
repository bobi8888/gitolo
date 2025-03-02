	#include "stdafx.h"

#include "MainMenuState.h"

//Initializer Methods
void MainMenuState::initVariables()
{
	//this->BackgroundTexture;
}

void MainMenuState::initFonts()
{
	if (!this->Font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf")) 
	{
		throw("ERROR::MainMenuState::Could not load font.");
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initGUI()
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
	this->buttons["NEW_GAME_BTN"] = new gui::Button(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(25.f, videoMode),
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(6.f, videoMode),
		&this->Font, "New Game", gui::calculateCharSize(videoMode),
		sf::Color::Black, sf::Color::Yellow, sf::Color::White, 
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200), 
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	this->buttons["EDITOR_BTN"] = new  gui::Button(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(32.f, videoMode),
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(6.f, videoMode),
		&this->Font, "Editor", gui::calculateCharSize(videoMode),
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	this->buttons["SETTINGS_BTN"] = new  gui::Button(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(39.f, videoMode),
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(6.f, videoMode),
		&this->Font, "Settings", gui::calculateCharSize(videoMode),
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);

	this->buttons["EXIT_BTN"] = new  gui::Button(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(46.f, videoMode),
		gui::convertToPixelsX(15.f, videoMode), gui::convertToPixelsY(6.f, videoMode),
		&this->Font, "Quit", gui::calculateCharSize(videoMode),
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);
}

void MainMenuState::resetGUI()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	this->buttons.clear();

	this->initGUI();
}

//Constructors & Destructor
MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();

	this->initFonts();

	this->initGUI();

	this->initKeybinds();
}

MainMenuState::~MainMenuState()
{	
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Update Methods
void MainMenuState::updatePlayerInput(const float& deltaTime)
{

	//for debugging?
/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) 
	{
	void;
	}*/		
}

void MainMenuState::updateButtons()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePositionWindow);
	}

	//New game
	if (this->buttons["NEW_GAME_BTN"]->isPressed())
	{
		this->statesStack->push(new GameState(this->stateData, "TOWN_SQUARE"));
	}

	//Editor
	if (this->buttons["EDITOR_BTN"]->isPressed())
	{
		this->statesStack->push(new EditorState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_BTN"]->isPressed())
	{
		this->statesStack->push(new SettingsState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_BTN"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& deltaTime)
{
	this->updateMousePositions();

	this->updatePlayerInput(deltaTime);

	this->updateButtons();

	//DEBUG
	//system("cls");
	//std::cout << this->MousePositionView.x << " " << this->MousePositionView.y;
}

//Render Methods
void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//Debugging
		sf::Text mouse_text;
		mouse_text.setPosition(sf::Vector2f(this->mousePositionView.x, this->mousePositionView.y + 15));
		mouse_text.setFont(this->Font);
		mouse_text.setCharacterSize(18);
		std::stringstream ss;
		ss << this->mousePositionView.x << "  " << this->mousePositionView.y;
		mouse_text.setString(ss.str());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			target->draw(mouse_text);
}
