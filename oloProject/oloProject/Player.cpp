#include "stdafx.h"

#include "Player.h"

//Initializer Methods
void Player::initVariables()
{
	this->isAttacking = false;
}

//Constructors/Destructors

Player::Player(sf::Texture& texture_sheet, float x, float y)
{
	this->initVariables();

	this->setPosition(x, y);

	//---------------------------maxVelo_accel_decel
	this->createMovementComponent(200.f, 500.f, 200.f);

	this->createAnimationComponent(texture_sheet);

	//_______________________________________key____timer___startX__startY__framesX_framesY__W___H
	
	//this->animationComponent->addAnimation("WALK",   10.f,    0,     2,      6,      2,   128, 128);
	//this->animationComponent->addAnimation("IDLE",   10.f,    0,     0,      5,      0,   128, 128);
	//this->animationComponent->addAnimation("ATTACK", 10.f,    0,     3,      4,      3,   128, 128);

	//Robo sprite
	this->animationComponent->addAnimation(
		"WALK", 10.f, 
		0, 2, 
		5, 2, 
		128, 128
	);

	this->animationComponent->addAnimation(
		"IDLE", 20.f, 
		0, 0, /*startX & startY*/
		5, 0, /*# of X frames & # of Y frames*/
		128, 128 /*width & height of frame*/
	);

	this->animationComponent->addAnimation(
		"ATTACK", 5.f, 
		0, 2, 
		5, 2, 
		128, 128
	);

	//4 frame knight
	//this->animationComponent->addAnimation("WALK_RIGHT",10.f,   0,     0,      4,      0,   96, 96);
	//this->animationComponent->addAnimation("WALK_LEFT", 10.f,   0,     1,      4,      1,   96, 96);
	//this->animationComponent->addAnimation("IDLE_RIGHT",40.f,   0,     2,      3,      2,   96, 96);
	//this->animationComponent->addAnimation("IDLE_LEFT", 40.f,   0,     3,      3,      3,   96, 96);
 
	//_______________________________sprite________offsetX_offsetY_width_height
	this->createHitboxComponent(this->sprite, 47.f, 58.f, 30.f, 70.f);

	//Robo sprite
	//this->createHitboxComponent(this->EntitySprite,  0.f,   0.f,  0.f,  0.f);

	this->createAttributeComponent(1);
}

Player::~Player()
{

}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

MovementComponent* Player::getMovementComponent()
{
	return this->movementComponent;
}

HitboxComponent* Player::getHitboxComponent()
{
	return this->hitboxComponent;
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
	else if (this->movementComponent->getDir(UP))
	{
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);

		this->animationComponent->play(
			"WALK", deltaTime,
			this->movementComponent->getVelo().y,
			this->movementComponent->getMaxVelo()
		);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);

		this->animationComponent->play(
			"WALK", deltaTime, 
			this->movementComponent->getVelo().x, 
			this->movementComponent->getMaxVelo()
		);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(128.f, 0.f);

		this->sprite.setScale(-1.f, 1.f);

		this->animationComponent->play(
			"WALK", deltaTime, 
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

	//system("cls");
	//std::cout << this->attributeComponent->debugPrint();
	
	this->movementComponent->update(deltaTime);

	this->updateAttack();

	this->updateAnimation(deltaTime);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}

void Player::updateLevel()
{
	this->attributeComponent->updateLevel();
}
