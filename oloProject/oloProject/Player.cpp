#include "Player.h"

//Initializer Methods
void Player::initVariables()
{

}

void Player::initComponents()
{

}



//Constructors/Destructors
Player::Player()
{
}
Player::Player(sf::Texture* texture, float x, float y)
{
	this->initVariables();
	this->initComponents();

	this->createSprite(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}
