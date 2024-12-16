#include "Button.h"

Button::Button()
{
}

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->ButtonState = BTN_IDLE;

	this->Rectangle.setSize(sf::Vector2f(width, height));
	this->Rectangle.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
	this->Rectangle.setPosition(sf::Vector2f(x, y));

	this->Font = font;

	this->Text.setFont(*this->Font);
	this->Text.setString(text);
	this->Text.setCharacterSize(12);
	this->Text.setOrigin(sf::Vector2f(this->Text.getGlobalBounds().width / 2.f, this->Text.getGlobalBounds().height / 2.f));
	this->Text.setPosition(this->Rectangle.getPosition());

	this->IdleColor = idleColor;
	this->HoverColor = hoverColor;
	this->ActiveColor = ActiveColor;
	this->Rectangle.setFillColor(this->IdleColor);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->ButtonState == BTN_ACTIVE)
		return true;
	else 
		return false;
}


void Button::update(const sf::Vector2f mousePos)
{
	this->ButtonState = BTN_IDLE;

	//check for hover
	if (this->Rectangle.getGlobalBounds().contains(mousePos)) 
	{
		this->ButtonState = BTN_HOVER;

		//check for press
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->ButtonState = BTN_ACTIVE;
		}
	}

	switch (this->ButtonState)
	{
		case BTN_IDLE:
			this->Rectangle.setFillColor(this->IdleColor);
			break;
		case BTN_HOVER:
			this->Rectangle.setFillColor(this->HoverColor);
			break;
		case BTN_ACTIVE:
			this->Rectangle.setFillColor(this->ActiveColor);
			break;
		default:
			this->Rectangle.setFillColor(sf::Color::Red);
			break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->Rectangle);
	target->draw(this->Text);
}
