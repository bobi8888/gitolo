#include "stdafx.h"
#include "HitboxComponent.h"

//Constructors & Destructor
HitboxComponent::HitboxComponent(
	sf::Sprite& sprite, 
	float offset_x, float offset_y, 
	float width, float height
	)	:sprite(sprite), xOffset(offset_x), yOffset(offset_y)
{
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setPosition(
		this->sprite.getPosition().x + offset_x, 
		this->sprite.getPosition().y + offset_y
	);

	this->hitbox.setFillColor(sf::Color(225, 220, 51, 150));

	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;
}

HitboxComponent::~HitboxComponent()
{

}
//Accessors
const sf::Vector2f& HitboxComponent::getPosition()
{
	return this->hitbox.getPosition(); 
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;

	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

//Modifiers
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);

	this->sprite.setPosition(
		position.x - this->xOffset, 
		position.y - this->yOffset
	);
}

void HitboxComponent::setPosition(const float& x, const float& y)
{
	this->hitbox.setPosition(x, y);

	this->sprite.setPosition(
		x - this->xOffset, 
		y - this->yOffset
	);
}

//Methods
bool HitboxComponent::isIntersecting(const sf::FloatRect& rect)
{
	return this->hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(
		this->sprite.getPosition().x + this->xOffset, 
		this->sprite.getPosition().y + this->yOffset
	);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
