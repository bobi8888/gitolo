#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	sf::Sprite& Sprite;

	sf::Vector2f Velocity;

	float MaxVelo;
	float Acceleration;
	float Deceleration;

	//Initializer Methods
	void initVariables();
public:
	//Constructors & Destructors
	MovementComponent(sf::Sprite& sprite, float maxVelo, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelo() const;
	const float& getMaxVelo() const;
	//Methods
	const bool getState(const short unsigned state) const;

	void move(const float xDir, const float yDir, const float& deltaTime);
	void update(const float &deltaTime);
};
