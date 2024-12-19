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
	this->Text.setFont(font);
	this->Text.setFillColor(sf::Color::Blue);
	this->Text.setCharacterSize(20);
	this->Text.setString("::PAUSED::");
	this->Text.setOrigin(sf::Vector2f(
		this->Text.getGlobalBounds().width / 2, 
		this->Text.getCharacterSize() / 2
		)
	);
	this->Text.setPosition(Container.getPosition().x, Container.getPosition().y - 100);

}

PauseMenu::~PauseMenu()
{
	for (auto it = this->Buttons.begin(); it != this->Buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Methods
void PauseMenu::update()
{

}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->Background);
	target.draw(this->Container);

	for (auto& i : this->Buttons)
	{
		i.second->render(target);
	}

	target.draw(this->Text);
}
