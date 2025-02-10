#include "stdafx.h"

#include "GUI.h"

//Constructors & Destructor
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
	this->Text.setOrigin(
		sf::Vector2f(
			this->Text.getGlobalBounds().width / 2.f, 
			this->Text.getCharacterSize() / 2.f
		)
	);
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

//const short unsigned& gui::Button::getButtonState() const
//{
//	return this->ButtonState;
//}

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
	this->Text.setOrigin(
		sf::Vector2f(
			this->Text.getGlobalBounds().width / 2.f, 
			this->Text.getCharacterSize() / 2.f
		)
	);

	this->Text.setPosition(this->Rectangle.getPosition());
}

void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	this->ButtonState = BTN_IDLE;

	//check for hover
	if (this->Rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) 
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

//Bar===============================================================================
//Constructords & Destructor

gui::Bar::Bar()
{
}

gui::Bar::Bar(sf::Vector2f position)
{
	this->BarBack.setSize(sf::Vector2f(15.f, 2.f));
	this->BarBack.setFillColor(sf::Color::Red);
	this->BarBack.setPosition(position);

	this->BarFront.setSize(sf::Vector2f(7.5f, 2.f));
	this->BarFront.setFillColor(sf::Color::Green);
	this->BarFront.setPosition(position);

}
gui::Bar::~Bar()
{

}

//Methods
void gui::Bar::update(const sf::Vector2f& position)
{
	this->BarBack.setPosition(position);

	this->BarFront.setPosition(position);
}

void gui::Bar::render(sf::RenderTarget& target)
{
	target.draw(this->BarBack);

	target.draw(this->BarFront);
}

//Dropdown List===============================================================================================
//Constructors & Destructor
gui::DropdownList::DropdownList(
	float xPos, float yPos, float width, float height, 
	sf::Font& font, std::string list[], 
	int elementsNum, unsigned default_index
	) : ListFont(font), ShowList(false)
{
	KeytimeMax = 1.f;

	Keytime = KeytimeMax;

	this->ActiveElement = new Button(
		xPos, yPos, width, height,
		&this->ListFont, list[default_index], 20,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200), 
		sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200)

	);

	for (int i = 0; i < elementsNum; i++)
	{
		this->ElementList.push_back(
			new Button(
				xPos, yPos + ((i + 1) * height), width, height,
				&this->ListFont, list[i], 20,
				sf::Color::Black, sf::Color::Yellow, sf::Color::White,
				sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
				sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200),
				i
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


//Accessors

const unsigned short& gui::DropdownList::getActiveElementId() const
{
	return this->ActiveElement->getId();
}

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

void gui::DropdownList::update(const sf::Vector2i& mousePosWindow, const float& deltaTime)
{
	this->updateKeytime(deltaTime);

	this->ActiveElement->update(mousePosWindow);

	if (this->ActiveElement->isPressed() && this->getKeytime())
		this->ShowList ? this->ShowList = false : this->ShowList = true;
	
	if (this->ShowList)
		for (auto &i : this->ElementList)
		{
			i->update(mousePosWindow);

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


//Texture Selector===========================================================================================
//Constructors & Destructor
gui::TextureSelector::TextureSelector(
	float x, float y,
	float width, float height,
	float gridSize,
	const sf::Texture* texture_sheet,
	sf::Font& font, std::string text
	) : keytimeMax(3.f), keytime(0.f)
{
	this->gridSize = gridSize;

	this->isActive = false;
	this->isHidden = true;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50,50,50,100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setFillColor(sf::Color(255,255,255,200));
	
	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(
			sf::IntRect(
				0, 0, 
				static_cast<int>(this->bounds.getGlobalBounds().width),
				static_cast<int>(this->sheet.getGlobalBounds().height)
			)
		);
	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(
			sf::IntRect(
				0, 0, 
				static_cast<int>(this->bounds.getGlobalBounds().height), 
				static_cast<int>(this->sheet.getGlobalBounds().width)
			)
		);
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hide_button = new gui::Button(
		37.5f, 15.f, 75.f, 30.f,
		&font, text, 15,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(74, 74, 74, 200), sf::Color(74, 74, 74, 255), sf::Color(24, 74, 74, 200)
	);
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_button;
}

//Accessors
const bool& gui::TextureSelector::getIsActive() const
{
	return this->isActive;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//const short unsigned& gui::TextureSelector::getButtonState() const
//{
//	return this->hide_button->getButtonState();
//}


//Methods
void gui::TextureSelector::update(const sf::Vector2i& mousePositionWindow, const float& deltaTime)
{
	this->updateKeytime(deltaTime);

	this->hide_button->update(mousePositionWindow);

	if (this->hide_button->isPressed() && this->getKeytime())
	{
		if (this->isHidden)
			this->isHidden = false;
		else
			this->isHidden = true;
	}

	if (!this->isHidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePositionWindow)))
		{
			this->isActive = true;
		}
		else
		{
			this->isActive = false;
		}

		if (this->isActive)
		{
			this->mousePostionGrid.x = (mousePositionWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePostionGrid.y = (mousePositionWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePostionGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePostionGrid.y * this->gridSize
			);

			//Update Texture Rectangle
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
				this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
			}
		}
	}
}

void gui::TextureSelector::updateKeytime(const float& deltaTime)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * deltaTime;
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	this->hide_button->render(target);

	if (!this->isHidden)
	{
		target.draw(this->bounds);

		target.draw(this->sheet);

		if (this->isActive)
			target.draw(this->selector);
	}
}

