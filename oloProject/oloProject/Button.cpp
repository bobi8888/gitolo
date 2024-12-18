#include "Button.h"

Button::Button()
{
}

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->ButtonState = BTN_IDLE;

	this->Rectangle.setSize(sf::Vector2f(width, height));
	this->Rectangle.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
	this->Rectangle.setPosition(sf::Vector2f(x, y));
	this->Rectangle.setFillColor(idle_color);

	this->Font = font;

	this->text.setFont(*this->Font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setOrigin(sf::Vector2f(this->text.getGlobalBounds().width / 2, this->text.getCharacterSize() / 2));
	this->text.setPosition(this->Rectangle.getPosition());

	this->TextIdleColor = text_idle_color;
	this->TextHoverColor = text_hover_color;
	this->TextActiveColor = text_active_color;

	this->IdleColor = idle_color;
	this->HoverColor = hover_color;
	this->ActiveColor = active_color;
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
			this->text.setFillColor(this->TextIdleColor);
			break;
		case BTN_HOVER:
			this->Rectangle.setFillColor(this->HoverColor);
			this->text.setFillColor(this->TextHoverColor);
			break;
		case BTN_ACTIVE:
			this->Rectangle.setFillColor(this->ActiveColor);
			this->text.setFillColor(this->TextActiveColor);
			break;
		default:
			this->Rectangle.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Black);
			break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->Rectangle);
	target->draw(this->text);
}
