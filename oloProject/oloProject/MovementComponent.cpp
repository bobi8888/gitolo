#include "stdafx.h"

#include "MovementComponent.h"

void MovementComponent::initVariables()
{
}

//Constructors & Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelo, float acceleration, float deceleration)
	:sprite(sprite), maxVelo(maxVelo), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//Methods
const sf::Vector2f& MovementComponent::getVelo()
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelo() const
{
	return this->maxVelo;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
		case IDLE:
			if (this->velocity.x == 0.f && this->velocity.y == 0)
				return true;
			break;
		case MOVING:
			if (this->velocity.x != 0.f || this->velocity.y != 0)
				return true;
			break;
		case MOVING_LEFT:
			if (this->velocity.x < 0.f)
				return true;
			break;
		case MOVING_RIGHT:
			if (this->velocity.x > 0.f)
				return true;
			break;
		case MOVING_UP:
			if (this->velocity.y < 0.f)
				return true;
			break;
		case MOVING_DOWN:
			if (this->velocity.y > 0.f)
				return true;
			break;
	}
	return false;
}

//Methods
void MovementComponent::move(const float xDir, const float yDir, const float& deltaTime)
{
	//Acceleration
	this->velocity.x += this->acceleration * xDir * deltaTime;

	this->velocity.y += this->acceleration * yDir * deltaTime;

	if (this->velocity.x > 0.f)
	{

	}
	else if (this->velocity.x < 0.f)
	{

	}

}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;

	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

void MovementComponent::update(const float& deltaTime)
{
	if (this->velocity.x > 0.f)
	{
		//Max Velo check x positive
		if (this->velocity.x > this->maxVelo)
			this->velocity.x = this->maxVelo;

		//Deceleration X positive
		this->velocity.x -= deceleration * deltaTime;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{
		//Max Velo check x negative
		if (this->velocity.x < -this->maxVelo)
			this->velocity.x = -this->maxVelo;
		
		//deceleration X negitive
		this->velocity.x += deceleration * deltaTime;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f)
	{
		//Max Velo check y positive
		if (this->velocity.y > this->maxVelo)
			this->velocity.y = this->maxVelo;

		//deceleration y positive
		this->velocity.y -= deceleration * deltaTime;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)
	{
		//Max Velo check y negative
		if (this->velocity.y < -this->maxVelo)
			this->velocity.y = -this->maxVelo;

		//deceleration y negitive
		this->velocity.y += deceleration * deltaTime;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final Movement
	this->sprite.move(this->velocity * deltaTime);
}
