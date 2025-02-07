#include "stdafx.h"

#include "Entity.h"

//Initializer Methods
void Entity::initVariables()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
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
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
	delete this->attributeComponent;
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
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelo, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->EntitySprite, maxVelo, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->EntitySprite, texture_sheet);
}

void Entity::createAttributeComponent()
{
	this->attributeComponent = new AttributeComponent(3);
}

//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->EntitySprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent){

		//std::cout << "hitboxComponent->getPosition().x: " << this->hitboxComponent->getPosition().x << "\n";
		//std::cout << "gridSizeI: " << gridSizeI << "\n";
		//std::cout << "x / gridSizeI: " << this->hitboxComponent->getPosition().x / gridSizeI << "\n";
		//std::cout << "cast int: " << static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI << "\n \n";

		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);
	}

	return sf::Vector2i(
		static_cast<int>(this->EntitySprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->EntitySprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->EntitySprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& deltaTime) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelo() * deltaTime);
	}

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Modifiers
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->EntitySprite.setPosition(x, y);
}
 
//Methods
void Entity::move(const float xDir, const float yDir, const float& deltaTime)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(xDir, yDir, deltaTime);//sets velo
	}
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();

}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::update(const float& deltaTime)
{
	if (this->movementComponent)
		this->movementComponent->update(deltaTime);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->EntitySprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
		
}
