#include "stdafx.h"

#include "GUI.h"

const float gui::convertToPixelsX(const float percent, const sf::VideoMode& videoMode)
{
	return std::floor(static_cast<float>(
		videoMode.width) * (percent / 100.f)
	);
}

const float gui::convertToPixelsY(const float percent, const sf::VideoMode& videoMode)
{
	return std::floor(static_cast<float>(
		videoMode.height) * (percent / 100.f)
	);
}

const unsigned gui::calculateCharSize( const sf::VideoMode& videoMode, const unsigned divisor)
{
	return static_cast<unsigned>((videoMode.width + videoMode.height) / divisor);
}

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
gui::Bar::Bar(
	const sf::VideoMode& video_Mode,
	const sf::Vector2f& position,
	const float width, const float height,
	const float x_Offset, const float y_Offset,
	const std::string font
	)
{
	this->maxWidth = gui::convertToPixelsX(width, video_Mode);
	this->height = gui::convertToPixelsY(height, video_Mode);
	this->xOffset = gui::convertToPixelsX(x_Offset, video_Mode);
	this->yOffset = gui::convertToPixelsY(y_Offset, video_Mode);

	this->barBack.setSize(sf::Vector2f(this->maxWidth, this->height));
	this->barBack.setFillColor(sf::Color::Red);
	this->barBack.setPosition(
		position.x + this->xOffset, 
		position.y + this->yOffset
	);

	this->barFront.setSize(sf::Vector2f(this->maxWidth, this->height));
	this->barFront.setFillColor(sf::Color::Green);
	this->barFront.setPosition(
		position.x + this->xOffset,
		position.y + this->yOffset
	);

	this->font.loadFromFile(font);

	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(gui::calculateCharSize(video_Mode, 120));
	this->text.setPosition(
		sf::Vector2f(
			barBack.getPosition().x + 10.f,
			barBack.getPosition().y + 20.f
		)
	);
}

gui::Bar::~Bar()
{

}

//Methods
void gui::Bar::updatePosition(const sf::Vector2f position)
{
	//FLOOR these

	this->barBack.setPosition(position.x + this->xOffset, position.y + this->yOffset);

	this->barFront.setPosition(position.x + this->xOffset, position.y + this->yOffset);

	this->text.setPosition(this->barBack.getPosition().x, this->barBack.getPosition().y);
}

void gui::Bar::updateText(std::string string)
{
	this->text.setString(string);
}

void gui::Bar::updateBarFrontSize(int value, int valueMax)
{
	float percent = static_cast<float>(value) / static_cast<float>(valueMax);

	this->barFront.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->maxWidth * percent)), 
			this->height
		)
	);
}

void gui::Bar::render(sf::RenderTarget& target)
{
	target.draw(this->barBack);

	target.draw(this->barFront);

	target.draw(this->text);
}

//Sphere=========================================================================================================

//Constructor & Destructor
//gui::Sphere::Sphere(float radius, sf::Vector2f position)
//{
//	this->circleBack.setRadius(radius);
//	this->circleBack.setOutlineThickness(1.f);
//	this->circleBack.setOutlineColor(sf::Color::White);
//	this->circleBack.setFillColor(sf::Color(250, 250, 250, 75));
//	this->circleBack.setPosition(position);
//	this->circleBack.setPointCount(30);
//
//	this->circleFront.setRadius(radius);
//	this->circleFront.setFillColor(sf::Color::Yellow);
//	this->circleFront.setPosition(position);
//	this->circleFront.setPointCount(30);
//
//	this->maxRadius = radius;
//}

gui::Sphere::Sphere(
	const sf::VideoMode& video_Mode, 
	const sf::Vector2f& position,
	const float radius, 
	const float x_Offset, const float y_Offset
	)
{
	this->maxRadius = gui::convertToPixelsX(radius, video_Mode);
	this->xOffset = gui::convertToPixelsX(x_Offset, video_Mode);
	this->yOffset = gui::convertToPixelsY(y_Offset, video_Mode);

	this->circleBack.setRadius(this->maxRadius);
	this->circleBack.setPointCount(30);
	this->circleBack.setOutlineThickness(1.f);
	this->circleBack.setOutlineColor(sf::Color::White);
	this->circleBack.setFillColor(sf::Color(250, 250, 250, 75));
	this->circleBack.setPosition(
		position.x + this->xOffset,
		position.y + this->yOffset
	);

	this->circleFront.setRadius(this->maxRadius);
	this->circleFront.setPointCount(30);
	this->circleFront.setFillColor(sf::Color::Yellow);
	this->circleFront.setPosition(
		position.x + this->xOffset,
		position.y + this->yOffset
	);
}

gui::Sphere::~Sphere()
{
}

//Methods
void gui::Sphere::updatePosition(const sf::Vector2f position)
{
	//FLOOR these
	this->circleBack.setPosition(
		static_cast<float>(std::floor(position.x + this->xOffset)),
		static_cast<float>(std::floor(position.y + this->yOffset))

		//position.x + this->xOffset, 
		//position.y + this->yOffset
	);

	this->circleFront.setOrigin(
		this->circleFront.getRadius(), 
		this->circleFront.getRadius()
	);

	this->circleFront.setPosition(
		static_cast<float>(std::floor(this->circleBack.getPosition().x + this->circleBack.getRadius())),
		static_cast<float>(std::floor(this->circleBack.getPosition().y + this->circleBack.getRadius()))
	);
}

void gui::Sphere::updateCircleFrontSize(int value, int valueMax)
{
	float percent = static_cast<float>(value) / static_cast<float>(valueMax);

	this->circleFront.setRadius(static_cast<float>(std::floor(this->maxRadius * percent)));
}

void gui::Sphere::render(sf::RenderTarget& target)
{
	target.draw(this->circleBack);

	target.draw(this->circleFront);
}

//Dropdown List===============================================================================================

//Constructors & Destructor
// 
//Settings: Resolution
gui::DropdownList::DropdownList(
	float xPos, float yPos, 
	float width, float height, 
	sf::Font& font, std::vector<std::string> list, unsigned char_size, 
	int elementsNum, std::vector<std::string> counterList
	) : font(font), showList(false)
{
	keytimeMax = 2.f;

	keytime = keytimeMax;

	this->activeElement = new Button(
		xPos, yPos, width, height,
		&this->font, "Resolutions", char_size,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
		sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200)
	);

	int validRes = 0;

	for (int i = 0; i < elementsNum; i++)
	{
		for (int j = 0; j < counterList.size(); j++) {

			if (list[i].compare(counterList[j]) == 0) {

				this->elementList.push_back(
					new Button(
						xPos, yPos + ((validRes++ + 1) * height), width, height,
						&this->font, list[i], char_size,
						sf::Color::Black, sf::Color::Yellow, sf::Color::White,
						sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
						sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200),
						i
					)
				);

				j = counterList.size();
			}
		}
	}
}

//Basic Constructor

gui::DropdownList::DropdownList(
	float xPos, float yPos, 
	float width, float height, 
	//sf::Font& font, std::string list[], unsigned char_size,
	sf::Font& font, std::vector<std::string> list, unsigned char_size,
	int elementsNum, unsigned default_index
	) : font(font), showList(false)
{
	keytimeMax = 2.f;

	keytime = keytimeMax;

	this->activeElement = new Button(
		xPos, yPos, width, height,
		&this->font, "Resolutions", char_size,
		sf::Color::Black, sf::Color::Yellow, sf::Color::White,
		sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200), 
		sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200)
	);

	int validRes = 0;
		
	for (int i = 0; i < elementsNum; i++) {

		//for (int j = 0; j < counterList.size(); j++) {

				this->elementList.push_back(
					new Button(
						xPos, yPos + ((validRes++ + 1) * height), width, height,
						&this->font, list[i], char_size,
						sf::Color::Black, sf::Color::Yellow, sf::Color::White,
						sf::Color(70, 70, 70, 200), sf::Color(70, 70, 70, 255), sf::Color(20, 70, 70, 200),
						sf::Color(174, 174, 174, 200), sf::Color(174, 174, 174, 255), sf::Color(124, 174, 174, 200),
						i
					)
				);

		//} 	
	}	
}

gui::DropdownList::~DropdownList()
{
	delete this->activeElement;

	for (auto &i : this->elementList)
		delete i;
}

//Accessors
const unsigned short& gui::DropdownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

const std::string& gui::DropdownList::getActiveElementTextString() const
{
	return this->activeElement->getText();
}

const bool gui::DropdownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;

		return true;
	}

	return false;
}

//Methods
void gui::DropdownList::updateKeytime(const float& deltaTime)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * deltaTime;	
}

void gui::DropdownList::update(const sf::Vector2i& mousePosWindow, const float& deltaTime)
{
	this->updateKeytime(deltaTime);

	this->activeElement->update(mousePosWindow);

	if (this->activeElement->isPressed() && this->getKeytime())
		this->showList ? this->showList = false : this->showList = true;
	
	if (this->showList)
		for (auto &i : this->elementList)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;

				this->activeElement->setText(i->getText());

				this->activeElement->centerText();

				this->activeElement->setId(i->getId());
			}
		}	
}

void gui::DropdownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
		for (auto& i : this->elementList)
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

	int textureRectWidth;
	int textureRectHeight;

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)

		textureRectWidth = static_cast<int>(this->bounds.getGlobalBounds().width);
	else
		textureRectWidth = static_cast<int>(this->sheet.getGlobalBounds().width);
	

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)

		textureRectHeight = static_cast<int>(this->bounds.getGlobalBounds().height);
	else 
		textureRectHeight = static_cast<int>(this->sheet.getGlobalBounds().height);
	
	this->sheet.setTextureRect(
		sf::IntRect(
			0, 0,
			textureRectWidth,
			textureRectHeight
		)
	);

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
