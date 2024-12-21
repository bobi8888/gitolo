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
	//this->BackgroundTexture;
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

void SettingsState::initButtons()
{
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color

	this->Buttons["EXIT_BTN"] = new gui::Button(100, 600, 150, 50,
		&this->Font, "Quit", 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200));

	std::string li[] = {"fire", "water", "earth", "air", "void"};
	this->ddl = new gui::DropdownList(200.f, 200.f, 75.f, 25.f, Font, li, 5);
}

//Constructors & Destructor
SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* statesStack)
	:State(window, supportedKeys, statesStack)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
	this->initKeybinds();
}

SettingsState::~SettingsState()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->ddl;
}

//Update Methods
void SettingsState::updatePlayerInput(const float& deltaTime)
{

	//for debugging?
/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
	void;
	}*/
}

void SettingsState::updateButtons()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->update(this->MousePositionView);
	}

	//  Quit State
	if (this->Buttons["EXIT_BTN"]->isPressed())
	{
		this->endState();
	}
}

void SettingsState::update(const float& deltaTime)
{
	this->updateMousePositions();
	this->updatePlayerInput(deltaTime);
	this->updateButtons();

	this->ddl->update(this->MousePositionView, deltaTime);
	//DEBUG


	//Debug
	//system("cls");
	//std::cout << this->MousePositionView.x << " " << this->MousePositionView.y;
}

//Render Methods
void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->Window;

	target->draw(this->Background);

	this->renderButtons(*target);
	this->ddl->render(*target);

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