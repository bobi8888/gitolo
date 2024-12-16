#include "Entity.h"

//Initializer Methods
void Entity::initVariables()
{
	this->Texture = nullptr;
	this->EntitySprite = nullptr;
	this->moveSpeed = 100.f;
}

void Entity::initComponents()
{

}

//Constructors & Destructors
Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->EntitySprite;
}

//Component Methods
void Entity::createSprite(sf::Texture* texture)
{
	this->Texture = texture;
	this->EntitySprite = new sf::Sprite(*this->Texture);
}

//Methods
void Entity::setPosition(const float x, const float y)
{
	if (this->EntitySprite)
		this->EntitySprite->setPosition(x, y);
}

void Entity::move(const float& deltaTime, const float xDir, const float yDir)
{
	if (this->EntitySprite)
		this->EntitySprite->move(xDir * moveSpeed * deltaTime, yDir * moveSpeed * deltaTime);
}

void Entity::update(const float& deltaTime)
{

}

void Entity::render(sf::RenderTarget* target)
{
	if (this->EntitySprite)
		target->draw(*this->EntitySprite);
}
