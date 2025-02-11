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
	this->sprite.setTexture(texture);
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
	this->movementComponent = new MovementComponent(this->sprite, maxVelo, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

//Accessors
const sf::Vector2f& Entity::getSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f& Entity::getHitboxPosition() const
{
	return this->hitboxComponent->getPosition();
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
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getSpriteGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getHitboxGlobalBounds() const
{
	return this->hitboxComponent->getGlobalBounds();
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
		this->sprite.setPosition(x, y);
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
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);		
}
