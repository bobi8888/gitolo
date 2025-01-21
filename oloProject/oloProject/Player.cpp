#include "stdafx.h"

#include "Player.h"

//Initializer Methods
void Player::initVariables()
{
	this->IsAttacking = false;
}

//Constructors/Destructors
Player::Player()
{
}

Player::Player(sf::Texture& texture_sheet, float x, float y)
{
	this->initVariables();

	this->setPosition(x, y);


	//---------------------------maxVelo_accel_decel
	this->createMovementComponent(200.f, 5.f, 2.f);
	this->createAnimationComponent(texture_sheet);
	//____________________________________________key________timer_startX_startY_framesX_framesY__W___H
	this->EntityAnimationComponent->addAnimation("WALK",   10.f,    0,     2,      6,      2,   128, 128);
	this->EntityAnimationComponent->addAnimation("IDLE",   10.f,    0,     0,      5,      0,   128, 128);
	this->EntityAnimationComponent->addAnimation("ATTACK", 10.f,    0,     3,      4,      3,   128, 128);
	//4 frame knight
//this->EntityAnimationComponent->addAnimation("WALK_RIGHT",10.f,   0,     0,      4,      0,   96, 96);
//this->EntityAnimationComponent->addAnimation("WALK_LEFT", 10.f,   0,     1,      4,      1,   96, 96);
//this->EntityAnimationComponent->addAnimation("IDLE_RIGHT",40.f,   0,     2,      3,      2,   96, 96);
//this->EntityAnimationComponent->addAnimation("IDLE_LEFT", 40.f,   0,     3,      3,      3,   96, 96);
	//_______________________________sprite________offsetX_offsetY_width_height
	this->createHitboxComponent(this->EntitySprite,  47.f,   58.f,  30.f,  70.f);

}

Player::~Player()
{

}

//Methods

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->IsAttacking = true;
	}
}

void Player::updateAnimation(const float& deltaTime)
{
	if (this->IsAttacking)
	{
		if (this->EntityAnimationComponent->play("ATTACK", deltaTime, true))
			this->IsAttacking = false;
	}
	else if (this->EntityMovementComponent->getState(MOVING_RIGHT))
	{
		this->EntitySprite.setOrigin(0.f, 0.f);
		this->EntitySprite.setScale(1.f, 1.f);
		this->EntityAnimationComponent->play("WALK", deltaTime, this->EntityMovementComponent->getVelo().x, this->EntityMovementComponent->getMaxVelo());
	}
	else if (this->EntityMovementComponent->getState(MOVING_LEFT))
	{
		this->EntitySprite.setOrigin(128.f, 0.f);
		this->EntitySprite.setScale(-1.f, 1.f);
		this->EntityAnimationComponent->play("WALK", deltaTime, this->EntityMovementComponent->getVelo().x, this->EntityMovementComponent->getMaxVelo());
	}
	else if (this->EntityMovementComponent->getState(IDLE))
	{
		this->EntityAnimationComponent->play("IDLE", deltaTime);
	}
}

void Player::update(const float& deltaTime)
{
	this->EntityMovementComponent->update(deltaTime);

	this->updateAttack();

	this->updateAnimation(deltaTime);

	this->EntityHitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->EntitySprite);

	this->EntityHitboxComponent->render(target);
}
