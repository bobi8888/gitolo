#include "HitboxComponent.h"

//Constructors & Destructor
HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:Sprite(sprite), OffsetX(offset_x), OffsetY(offset_y)
{
	this->Hitbox.setSize(sf::Vector2f(width, height));
	this->Hitbox.setPosition(this->Sprite.getPosition().x + offset_x, this->Sprite.getPosition().y + offset_y);

	this->Hitbox.setFillColor(sf::Color::Transparent);
	this->Hitbox.setOutlineThickness(1.f);
	this->Hitbox.setOutlineColor(sf::Color::Magenta);
}

HitboxComponent::~HitboxComponent()
{

}
//Methods

bool HitboxComponent::isIntersecting(const sf::FloatRect& rect)
{
	return this->Hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update()
{
	this->Hitbox.setPosition(this->Sprite.getPosition().x + this->OffsetX, this->Sprite.getPosition().y + this->OffsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->Hitbox);
}
