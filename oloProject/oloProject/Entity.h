#pragma once
#include "MovementComponent.h"

class Entity
{
private:
	//Initializer Methods
	void initVariables();
	void initComponents();

protected:
	sf::Texture* Texture;
	sf::Sprite* EntitySprite;

	float moveSpeed;

public:
	//Constructors & Destructors
	Entity();
	virtual ~Entity();

	//Component Methods
	void createSprite(sf::Texture* texture);

	//Methods
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& deltaTime, const float xDir, const float yDir);
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);
};

