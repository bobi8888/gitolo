#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	//Initializer Methods
	void initVariables();
	void initComponents();

protected:
	sf::Sprite EntitySprite;

	MovementComponent* EntityMovementComponent;
	AnimationComponent* EntityAnimationComponent;
public:
	//Constructors & Destructors
	Entity();
	virtual ~Entity();

	//Component Methods
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelo, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Methods
	virtual void setPosition(const float x, const float y);
	virtual void move(const float xDir, const float yDir, const float& deltaTime);
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);
};

