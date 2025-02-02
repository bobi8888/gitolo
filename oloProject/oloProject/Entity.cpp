#include "stdafx.h"

#include "Entity.h"

//Initializer Methods
void Entity::initVariables()
{
	this->EntityMovementComponent = nullptr;
	this->EntityAnimationComponent = nullptr;
	this->EntityHitboxComponent = nullptr;
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
	delete this->EntityHitboxComponent;
}

//Component Methods
void Entity::setTexture(sf::Texture& texture)
{
	this->EntitySprite.setTexture(texture);
}

void Entity::createHitboxComponent(
	sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height
)
{
	this->EntityHitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelo, const float acceleration, const float deceleration)
{
	this->EntityMovementComponent = new MovementComponent(this->EntitySprite, maxVelo, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->EntityAnimationComponent = new AnimationComponent(this->EntitySprite, texture_sheet);
}


//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (this->EntityHitboxComponent)
		return this->EntityHitboxComponent->getPosition();

	return this->EntitySprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->EntityHitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->EntityHitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->EntityHitboxComponent->getPosition().y) / gridSizeI
			);
	
	return sf::Vector2i(
		static_cast<int>(this->EntitySprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->EntitySprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->EntityHitboxComponent)
		return this->EntityHitboxComponent->getGlobalBounds();

	return this->EntitySprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& deltaTime) const
{
	if (this->EntityHitboxComponent && this->EntityMovementComponent)
	{
		return this->EntityHitboxComponent->getNextPosition(this->EntityMovementComponent->getVelo() * deltaTime);
	}

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Modifiers
void Entity::setPosition(const float x, const float y)
{
	if (this->EntityHitboxComponent)
		this->EntityHitboxComponent->setPosition(x, y);
	else
		this->EntitySprite.setPosition(x, y);
}
 
//Methods
void Entity::move(const float xDir, const float yDir, const float& deltaTime)
{
	if (this->EntityMovementComponent)
	{
		this->EntityMovementComponent->move(xDir, yDir, deltaTime);//sets velo
	}
}

void Entity::stopVelocity()
{
	if (this->EntityMovementComponent)
		this->EntityMovementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->EntityMovementComponent)
		this->EntityMovementComponent->stopVelocityX();

}

void Entity::stopVelocityY()
{
	if (this->EntityMovementComponent)
		this->EntityMovementComponent->stopVelocityY();
}

void Entity::update(const float& deltaTime)
{
	if (this->EntityMovementComponent)
		this->EntityMovementComponent->update(deltaTime);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->EntitySprite);

	if (this->EntityHitboxComponent)
		this->EntityHitboxComponent->render(target);
		
}
