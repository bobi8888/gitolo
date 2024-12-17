#include "Player.h"

//Initializer Methods
void Player::initVariables()
{

}

void Player::initComponents()
{
	//_______________________Max Velo, Acceleration, Deceleration
	this->createMovementComponent(200.f, 10.f, 4.f);
}

//Constructors/Destructors
Player::Player()
{
}
Player::Player(sf::Texture& texture, float x, float y)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}
