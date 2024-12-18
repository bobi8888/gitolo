#include "Player.h"

//Initializer Methods
void Player::initVariables()
{

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
	this->createMovementComponent(200.f, 20.f, 9.f);
	this->createAnimationComponent(texture_sheet);
	//____________________________________________key________timer_startX_startY_framesX_framesY__W___H
	this->EntityAnimationComponent->addAnimation("WALK_RIGHT",10.f,   0,     0,      4,      0,   96, 96);
	this->EntityAnimationComponent->addAnimation("WALK_LEFT", 10.f,   0,     1,      4,      1,   96, 96);
	this->EntityAnimationComponent->addAnimation("IDLE_RIGHT",40.f,  0,     2,      3,      2,   96, 96);
	this->EntityAnimationComponent->addAnimation("IDLE_LEFT", 40.f,  0,     3,      3,      3,   96, 96);
}

Player::~Player()
{

}

//Methods
void Player::update(const float& deltaTime)
{
	this->EntityMovementComponent->update(deltaTime);

	if (this->EntityMovementComponent->getState(IDLE))		
		this->EntityAnimationComponent->play("IDLE_RIGHT", deltaTime);

	else if (this->EntityMovementComponent->getState(MOVING_RIGHT))
		this->EntityAnimationComponent->play("WALK_RIGHT", deltaTime);

	else if (this->EntityMovementComponent->getState(MOVING_LEFT))
		this->EntityAnimationComponent->play("WALK_LEFT", deltaTime);
}
