#include "MainMenuState.h"

//Initializer Methods
void MainMenuState::initBackground()
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

void MainMenuState::initButtons()
{	
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color
	this->Buttons["NEW_GAME_BTN"] = new Button(100, 100, 150, 50, 
		&this->Font, "New Game", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White, 
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200));
	
	this->Buttons["EDITOR_BTN"] = new Button(100, 250, 150, 50,
		&this->Font, "Editor", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200));

	this->Buttons["SETTINGS_BTN"] = new Button(100, 500, 150, 50, 
		&this->Font, "Settings", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200));

	this->Buttons["EXIT_BTN"] = new Button(100, 600, 150, 50, 
		&this->Font, "Quit", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200));
}

//Constructors & Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	: State(window, supportedKeys, statesStack)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
	this->initKeybinds();

	//DEBUG
}

MainMenuState::~MainMenuState()
{	
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Update Methods
void MainMenuState::updateKeyInput(const float& deltaTime)
{

	//for debugging?
/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) 
	{
	void;
	}*/		
}

void MainMenuState::updateButtons()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->update(this->MousePositionView);
	}

	//New game
	if (this->Buttons["NEW_GAME_BTN"]->isPressed())
	{
		this->StatesStack->push(new GameState(this->Window, this->SupportedKeys, this->StatesStack));
	}

	//Editor
	if (this->Buttons["EDITOR_BTN"]->isPressed())
	{
		this->StatesStack->push(new EditorState(this->Window, this->SupportedKeys, this->StatesStack));
	}

	//Settings

	//Quit the game
	if (this->Buttons["EXIT_BTN"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeyInput(deltaTime);
	this->updateButtons();

	//DEBUG


	//Debug
	//system("cls");
	//std::cout << this->MousePositionView.x << " " << this->MousePositionView.y;
}

//Render Methods
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;

	target->draw(this->Background);

	this->renderButtons(target);

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
