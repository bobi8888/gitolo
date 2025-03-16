#include "stdafx.h"

#include "Player.h"

//Initializer Methods
void Player::initVariables()
{
	this->isAttacking = false;
}

//Constructors/Destructors
Player::Player(sf::Texture& texture_sheet, float xPosition, float yPosition)
{
	this->initVariables();

	this->setPosition(xPosition, yPosition);

	//---------------------------maxVelo_accel_decel
	this->createMovementComponent(200.f, 500.f, 200.f);

	this->createAnimationComponent(texture_sheet);

	//Animations
	this->animationComponent->addAnimation(
		"IDLE", 8.f, /*name & speed*/
		0, 0, /* startX & startY*/
		5, 0, /* index of X frames & index of Y frames*/
		100, 100 /* width & height of frame*/
	);

	this->animationComponent->addAnimation(
		"WALK_UP", 6.f,
		0, 1,
		5, 1,
		100, 100
	);

	this->animationComponent->addAnimation(
		"WALK_DOWN", 6.f,
		0, 2,
		5, 2,
		100, 100
	);

	this->animationComponent->addAnimation(
		"WALK_LEFT", 6.f,
		0, 3,
		5, 3,
		100, 100
	);

	this->animationComponent->addAnimation(
		"WALK_RIGHT", 6.f, 
		0, 4, 
		5, 4, 
		100, 100
	);

	this->animationComponent->addAnimation(
		"ATTACK", 4.f, 
		0, 0, 
		5, 0, 
		100, 100
	);
 
	this->createHitboxComponent(
		this->sprite, 
		30.f, 20.f, /* x & y offset*/
		40.f, 80.f /* width & height*/
	);

	this->createWeaponHitboxComponent(
		this->sprite,
		40.f, 20.f, /* x & y offset*/
		50.f, 80.f /* width & height*/
	);

	createPlayerAttributeComponent(true, 1);
}

Player::~Player()
{

}

MovementComponent* Player::getMovementComponent()
{
	return this->movementComponent;
}

HitboxComponent* Player::getHitboxComponent()
{
	return this->hitboxComponent;
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//Methods
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isAttacking = true;
	}
}

void Player::gainExp(const int gainedExp)
{
	this->attributeComponent->gainExp(gainedExp);
}

void Player::updateAnimation(const float& deltaTime)
{
	if (this->isAttacking)
	{
		if (this->animationComponent->play("ATTACK", deltaTime, true))
			this->isAttacking = false;
	}
	//else if (this->movementComponent->getDir(UP))
	//{
	//	this->sprite.setOrigin(0.f, 0.f);

	//	this->sprite.setScale(1.f, 1.f);

	//	this->animationComponent->play(
	//		"WALK", deltaTime,
	//		this->movementComponent->getVelo().y,
	//		this->movementComponent->getMaxVelo()
	//	);
	//}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);

		this->animationComponent->play(
			"WALK_UP", deltaTime,
			this->movementComponent->getVelo().x,
			this->movementComponent->getMaxVelo()
		);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);

		this->animationComponent->play(
			"WALK_DOWN", deltaTime,
			this->movementComponent->getVelo().x,
			this->movementComponent->getMaxVelo()
		);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);

		this->animationComponent->play(
			"WALK_LEFT", deltaTime,
			this->movementComponent->getVelo().x,
			this->movementComponent->getMaxVelo()
		);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);

		this->animationComponent->play(
			"WALK_RIGHT", deltaTime, 
			this->movementComponent->getVelo().x, 
			this->movementComponent->getMaxVelo()
		);
	}
	else if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", deltaTime);
	}
}

void Player::update(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->gainExp(15);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		loseHp(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		gainHp(1);
	
	this->movementComponent->update(deltaTime);

	this->updateAttack();

	this->updateAnimation(deltaTime);

	this->hitboxComponent->update();

	this->weaponHitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, const bool showHitboxes)
{
	target.draw(this->sprite);

	if (showHitboxes)
	{
		this->hitboxComponent->render(target);

		this->weaponHitboxComponent->render(target);
	}
}

void Player::updateLevel()
{
	this->attributeComponent->updateLevel();
}
