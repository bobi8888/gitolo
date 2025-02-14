#include "stdafx.h"

#include "PauseMenu.h"

//Constructors & Desctructor
PauseMenu::PauseMenu(sf::VideoMode& video_Mode,sf::Font& font)
	: font(font)
{
	//Init Background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(video_Mode.width),
			static_cast<float>(video_Mode.height)
		)
	);

	this->background.setOrigin(
		sf::Vector2f(
			background.getSize().x / 2.f, 
			background.getSize().y / 2.f
		)
	);

	this->background.setPosition(
		sf::Vector2f(
			static_cast<float>(video_Mode.width / 2.f),
			static_cast<float>(video_Mode.height / 2.f)
		)
	);

	this->background.setFillColor(sf::Color(20,20,20,100));
	
	//Init Container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(video_Mode.width / 3.f),
			static_cast<float>(video_Mode.height / 2.f)
		)
	);

	this->container.setOrigin(
		sf::Vector2f(
			container.getSize().x / 2.f,
			container.getSize().y / 2.f
		)
	);

	this->container.setPosition(this->background.getPosition());

	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	//Init Font
	this->text.setFont(font);

	this->text.setFillColor(sf::Color::Blue);

	this->text.setCharacterSize(gui::calculateCharSize(video_Mode));

	this->text.setString("::PAUSED::");

	this->text.setOrigin(sf::Vector2f(
		this->text.getGlobalBounds().width / 2,
		static_cast<float>(this->text.getCharacterSize()) / 2.f
		)
	);

	this->text.setPosition(
		container.getPosition().x, 
		container.getPosition().y - gui::convertToPixelsY(22.5f, video_Mode)
	);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Methods
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
	const float xPos, const float yPos,	
	const float width, const float height,
	const std::string key, const std::string text, const unsigned char_size 
	)
{	
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color
	this->buttons[key] = new gui::Button(
		xPos, yPos, width, height,
		&this->font, text, char_size,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);
}

void PauseMenu::update(const sf::Vector2i& mouse_Pos_Window)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mouse_Pos_Window);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->text);
}

sf::RectangleShape PauseMenu::getContainer()
{
	return this->container;
}
