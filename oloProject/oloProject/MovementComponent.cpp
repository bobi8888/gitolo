#include "MovementComponent.h"

void MovementComponent::initVariables()
{
}

//Constructors & Destructors
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelo, float acceleration, float deceleration)
	:Sprite(sprite), MaxVelo(maxVelo), Acceleration(acceleration), Deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelo() const
{
	return this->Velocity;
}

//Methods
void MovementComponent::move(const float xDir, const float yDir, const float& deltaTime)
{
	//Acceleration
	this->Velocity.x += this->Acceleration * xDir;

	if (this->Velocity.x > 0.f)
	{

	}
	else if (this->Velocity.x < 0.f)
	{

	}

	this->Velocity.y += this->Acceleration * yDir;


}

void MovementComponent::update(const float& deltaTime)
{
	if (this->Velocity.x > 0.f)
	{
		//Max Velo check x positive
		if (this->Velocity.x > this->MaxVelo)
			this->Velocity.x = this->MaxVelo;

		//Deceleration X positive
		this->Velocity.x -= Deceleration;
		if (this->Velocity.x < 0.f)
			this->Velocity.x = 0.f;
	}
	else if (this->Velocity.x < 0.f)
	{
		//Max Velo check x negative
		if (this->Velocity.x < -this->MaxVelo)
			this->Velocity.x = -this->MaxVelo;
		
		//Deceleration X negitive
		this->Velocity.x += Deceleration;
		if (this->Velocity.x > 0.f)
			this->Velocity.x = 0.f;
	}

	if (this->Velocity.y > 0.f)
	{
		//Max Velo check y positive
		if (this->Velocity.y > this->MaxVelo)
			this->Velocity.y = this->MaxVelo;

		//Deceleration y positive
		this->Velocity.y -= Deceleration;
		if (this->Velocity.y < 0.f)
			this->Velocity.y = 0.f;
	}
	else if (this->Velocity.y < 0.f)
	{
		//Max Velo check y negative
		if (this->Velocity.y < -this->MaxVelo)
			this->Velocity.y = -this->MaxVelo;

		//Deceleration y negitive
		this->Velocity.y += Deceleration;
		if (this->Velocity.y > 0.f)
			this->Velocity.y = 0.f;
	}

	//Final Movement
	this->Sprite.move(this->Velocity * deltaTime);
}
