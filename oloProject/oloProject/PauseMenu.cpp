#include "PauseMenu.h"

//Constructors & Desctructor
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: Font(font)
{
	//Init Background
	this->Background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y)
		)
	);

	this->Background.setOrigin(sf::Vector2f(
		Background.getSize().x / 2.f, 
		Background.getSize().y / 2.f
		)
	);

	this->Background.setPosition(sf::Vector2f(
		static_cast<float>(window.getSize().x / 2.f),
		static_cast<float>(window.getSize().y / 2.f)
		)
	);

	this->Background.setFillColor(sf::Color(20,20,20,100));
	
	//Init Container
	this->Container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 3.f,
		static_cast<float>(window.getSize().y / 2.f)
		)
	);

	this->Container.setOrigin(sf::Vector2f(
		Container.getSize().x / 2.f,
		Container.getSize().y / 2.f
		)
	);

	this->Container.setPosition(this->Background.getPosition());

	this->Container.setFillColor(sf::Color(20, 20, 20, 200));

	//Init Font
	this->MenuText.setFont(font);
	this->MenuText.setFillColor(sf::Color::Blue);
	this->MenuText.setCharacterSize(20);
	this->MenuText.setString("::PAUSED::");
	this->MenuText.setOrigin(sf::Vector2f(
		this->MenuText.getGlobalBounds().width / 2,
		this->MenuText.getCharacterSize() / 2
		)
	);
	this->MenuText.setPosition(Container.getPosition().x, Container.getPosition().y - 150.f);

}

PauseMenu::~PauseMenu()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->Buttons;
}

//Methods
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->Buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, const std::string text, float xPos, float yPos)
{
	float width = 150.f;
	float height = 50.f;
	//xPos, yPos, width, height,
	//font, textString, char_size, 
	//text idle color, text hover color, text active color,
	//idle color, hover color, active color
	this->Buttons[key] = new Button(
		xPos, yPos, width, height,
		&this->Font, text, 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200)
	);
}

void PauseMenu::update(const sf::Vector2f mousePos)
{
	for (auto &i : this->Buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->Background);
	target.draw(this->Container);

	for (auto& i : this->Buttons)
	{
		i.second->render(target);
	}

	target.draw(this->MenuText);
}

sf::RectangleShape PauseMenu::getContainer()
{
	return this->Container;
}
