#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	sf::Sprite& sprite;

	sf::Vector2f velocity;

	float maxVelo;
	float acceleration;
	float deceleration;

	//Initializer Methods
	void initVariables();

public:
	//Constructors & Destructors
	MovementComponent(sf::Sprite& sprite, float maxVelo, float acceleration, float deceleration);

	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelo();

	const float& getMaxVelo() const;

	const bool getState(const short unsigned state) const;

	//Methods
	void move(const float xDir, const float yDir, const float& deltaTime);

	void stopVelocity();

	void stopVelocityX();

	void stopVelocityY();

	void update(const float &deltaTime);
};
