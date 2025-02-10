#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

enum facing_dir {UP = 0, DOWN, LEFT, RIGHT};

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

	const bool getDir(const short unsigned dir) const;

	const sf::Vector2f& getSpritePosition() const;

	//Methods
	void move(const float xDir, const float yDir, const float& deltaTime);

	void stopVelocity();

	void stopVelocityX();

	void stopVelocityY();

	void update(const float &deltaTime);
};
