#include "GUI.h"

gui::Button::Button()
{
}

gui::Button::Button(float x, float y, float width, float height, 
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

	this->Text.setFont(*this->Font);
	this->Text.setString(text);
	this->Text.setFillColor(text_idle_color);
	this->Text.setCharacterSize(character_size);
	this->Text.setOrigin(sf::Vector2f(this->Text.getGlobalBounds().width / 2, this->Text.getCharacterSize() / 2));
	this->Text.setPosition(this->Rectangle.getPosition());

	this->TextIdleColor = text_idle_color;
	this->TextHoverColor = text_hover_color;
	this->TextActiveColor = text_active_color;

	this->IdleColor = idle_color;
	this->HoverColor = hover_color;
	this->ActiveColor = active_color;
}

gui::Button::~Button()
{
}

//Accessors
const bool gui::Button::isPressed() const
{
	if (this->ButtonState == BTN_ACTIVE)
		return true;
	else 
		return false;
}

const std::string& gui::Button::getText() const
{
	return this->Text.getString();;
}

//Modifers
void gui::Button::setText(const std::string text)
{
	this->Text.setString(text);
}

//Methods
void gui::Button::update(const sf::Vector2f mousePos)
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
			this->Text.setFillColor(this->TextIdleColor);
			break;
		case BTN_HOVER:
			this->Rectangle.setFillColor(this->HoverColor);
			this->Text.setFillColor(this->TextHoverColor);
			break;
		case BTN_ACTIVE:
			this->Rectangle.setFillColor(this->ActiveColor);
			this->Text.setFillColor(this->TextActiveColor);
			break;
		default:
			this->Rectangle.setFillColor(sf::Color::Red);
			this->Text.setFillColor(sf::Color::Black);
			break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->Rectangle);
	target.draw(this->Text);
}

//Dropdown List
//Constructors & Destructor
gui::DropdownList::DropdownList(float xPos, float yPos, float width, float height, sf::Font& font, std::string list[], unsigned elementsNum, unsigned default_index)
	: ListFont(font), ShowList(false), KeytimeMax(1.f), Keytime(KeytimeMax)
{
	std::string li[] = { "fire", "water", "earth", "air", "void" };

	for (size_t i = 0; i < elementsNum; i++)
	{
		this->ElementList.push_back(
			new Button(
				xPos, yPos + i * height, width, height,
				&this->ListFont, li[i], 20,
				sf::Color::Black, sf::Color::Yellow, sf::Color::White,
				sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200)
			)
		);
	}

	this->ActiveElement = new Button(*this->ElementList[default_index]);
}

gui::DropdownList::~DropdownList()
{
	delete this->ActiveElement;

	for (auto &i : this->ElementList)
		delete i;
}

//Accessor Methods

const bool gui::DropdownList::getKeytime()
{
	if (this->Keytime >= this->KeytimeMax)
	{
		this->Keytime = 0.f;
		return true;
	}

	return false;
}

//Methods
void gui::DropdownList::updateKeytime(const float& deltaTime)
{
	if (this->Keytime < this->KeytimeMax)
		this->Keytime += 10.f * deltaTime;
	
}

void gui::DropdownList::update(const sf::Vector2f& mousePos, const float& deltaTime)
{
	this->updateKeytime(deltaTime);
	this->ActiveElement->update(mousePos);

	if (this->ActiveElement->isPressed() && this->getKeytime())
		this->ShowList ? this->ShowList = false : this->ShowList = true;
	
	if (this->ShowList)
		for (auto &i : this->ElementList)
			i->update(mousePos);
		
	
}

void gui::DropdownList::render(sf::RenderTarget& target)
{
	this->ActiveElement->render(target);

	if (this->ShowList)
		for (auto& i : this->ElementList)
			i->render(target);
		
	
}
