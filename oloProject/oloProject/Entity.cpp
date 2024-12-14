#include "Entity.h"

Entity::Entity()
{
	this->Rectangle.setSize(sf::Vector2f(100.f, 100.f));
	this->moveSpeed = 100.f;
}

Entity::~Entity()
{
}

void Entity::move(const float& deltaTime, const float xDir, const float yDir)
{
	this->Rectangle.move(xDir * moveSpeed * deltaTime, yDir * moveSpeed * deltaTime);
}

void Entity::update(const float& deltaTime)
{

}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->Rectangle);
}
