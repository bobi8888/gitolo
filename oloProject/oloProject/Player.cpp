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

	this->createMovementComponent(200.f, 10.f, 4.f);
	this->createAnimationComponent(texture_sheet);
	//____________________________________________key________timer_startX_startY_framesX_framesY__W___H
	this->EntityAnimationComponent->addAnimation("WALK_RIGHT",5.f,   0,     0,      4,      0,   96, 96);
	this->EntityAnimationComponent->addAnimation("WALK_LEFT", 5.f,   0,     1,      4,      1,   96, 96);
	this->EntityAnimationComponent->addAnimation("IDLE_RIGHT",30.f,  0,     2,      3,      2,   96, 96);
	this->EntityAnimationComponent->addAnimation("IDLE_LEFT", 30.f,  0,     3,      3,      3,   96, 96);
}

Player::~Player()
{

}

//Methods
void Player::update(const float& deltaTime)
{
	this->EntityMovementComponent->update(deltaTime);

	if (this->EntityMovementComponent->isIdle())		
		this->EntityAnimationComponent->play("IDLE_RIGHT", deltaTime);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->EntityAnimationComponent->play("WALK_RIGHT", deltaTime);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->EntityAnimationComponent->play("WALK_LEFT", deltaTime);

	else 
		this->EntityAnimationComponent->play("IDLE_LEFT", deltaTime);
}
