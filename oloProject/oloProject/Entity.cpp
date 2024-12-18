#include "Entity.h"

//Initializer Methods
void Entity::initVariables()
{
	this->EntityMovementComponent = nullptr;
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
	delete this->EntityMovementComponent;
	delete this->EntityAnimationComponent;
}

//Component Methods
void Entity::setTexture(sf::Texture& texture)
{
	this->EntitySprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelo, const float acceleration, const float deceleration)
{
	this->EntityMovementComponent = new MovementComponent(this->EntitySprite, maxVelo, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->EntityAnimationComponent = new AnimationComponent(this->EntitySprite, texture_sheet);
}

//Methods
void Entity::setPosition(const float x, const float y)
{
	this->EntitySprite.setPosition(x, y);
}

void Entity::move(const float xDir, const float yDir, const float& deltaTime)
{
	if (this->EntityMovementComponent)
	{
		this->EntityMovementComponent->move(xDir, yDir, deltaTime);//sets velo
	}
}

void Entity::update(const float& deltaTime)
{
	if (this->EntityMovementComponent)
		this->EntityMovementComponent->update(deltaTime);
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->EntitySprite);
}
