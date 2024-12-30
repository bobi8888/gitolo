#include "GUI.h"

gui::Button::Button()
{
}

gui::Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle, sf::Color text_hover, sf::Color text_active,
	sf::Color idle, sf::Color hover, sf::Color active,
	sf::Color outlineIdle, sf::Color outlineHover, sf::Color outlineActive,
	short unsigned buttonId
	)
{
	this->ButtonState = BTN_IDLE;
	this->ButtonId = buttonId;

	this->Rectangle.setSize(sf::Vector2f(width, height));
	this->Rectangle.setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
	this->Rectangle.setPosition(sf::Vector2f(x, y));
	this->Rectangle.setFillColor(idle);
	this->Rectangle.setOutlineThickness(1.f);
	this->Rectangle.setOutlineColor(outlineIdle);

	this->Font = font;

	this->Text.setFont(*this->Font);
	this->Text.setString(text);
	this->Text.setFillColor(text_idle);
	this->Text.setCharacterSize(character_size);
	this->Text.setOrigin(sf::Vector2f(this->Text.getGlobalBounds().width / 2, this->Text.getCharacterSize() / 2));
	this->Text.setPosition(this->Rectangle.getPosition());

	this->TextIdleColor = text_idle;
	this->TextHoverColor = text_hover;
	this->TextActiveColor = text_active;

	this->IdleColor = idle;
	this->HoverColor = hover;
	this->ActiveColor = active;

	this->OutlineIdleColor = outlineIdle;
	this->OutlineHoverColor = outlineHover;
	this->OutlineActiveColor = outlineActive;
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

const std::string gui::Button::getText() const
{
	return this->Text.getString();;
}

const short unsigned& gui::Button::getId() const
{
	return this->ButtonId;
}

//Modifers
void gui::Button::setText(const std::string text)
{
	this->Text.setString(text);
	//update the position of the text so that it is centered?
}

void gui::Button::setId(const short unsigned id)
{
	this->ButtonId = id;
}

//Methods
void gui::Button::centerText() {
	this->Text.setOrigin(sf::Vector2f(this->Text.getGlobalBounds().width / 2, this->Text.getCharacterSize() / 2));
	this->Text.setPosition(this->Rectangle.getPosition());
}

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
			this->Text.setOutlineColor(this->OutlineIdleColor);
			break;
		case BTN_HOVER:
			this->Rectangle.setFillColor(this->HoverColor);
			this->Text.setFillColor(this->TextHoverColor);
			this->Text.setOutlineColor(this->OutlineHoverColor);
			break;
		case BTN_ACTIVE:
			this->Rectangle.setFillColor(this->ActiveColor);
			this->Text.setFillColor(this->TextActiveColor);
			this->Text.setOutlineColor(this->OutlineActiveColor);
			break;
		default:
			this->Rectangle.setFillColor(sf::Color::Red);
			this->Text.setFillColor(sf::Color::Black);
			this->Text.setOutlineColor(sf::Color::Green);
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
	this->ActiveElement = new Button(
		xPos, yPos, width, height,
		&this->ListFont, list[default_index], 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200), 
		sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200)

	);

	for (size_t i = 0; i < elementsNum; i++)
	{
		this->ElementList.push_back(
			new Button(
				xPos, yPos + ((i + 1) * height), width, height,
				&this->ListFont, list[i], 20,
				sf::Color::Black, sf::Color::Yellow, sf::Color::White,
				sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
				sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200)
			)
		);
	}
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
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->ShowList = false;

				this->ActiveElement->setText(i->getText());

				this->ActiveElement->centerText();

				this->ActiveElement->setId(i->getId());
			}
		}	
}

void gui::DropdownList::render(sf::RenderTarget& target)
{
	this->ActiveElement->render(target);

	if (this->ShowList)
		for (auto& i : this->ElementList)
			i->render(target);	
}
