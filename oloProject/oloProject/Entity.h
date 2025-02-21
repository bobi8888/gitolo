#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"

class MovementComponent;
class AnimationComponent;
class HitboxComponent;
class AttributeComponent;

class Entity
{
private:
	//Initializer Methods
	void initVariables();
	void initComponents();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	AttributeComponent* attributeComponent;

public:
	//Constructors & Destructors
	Entity();
	virtual ~Entity();

	//Component Methods
	void setTexture(sf::Texture& texture);

	void createHitboxComponent(
		sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height
	);

	void createMovementComponent(const float maxVelo, const float acceleration, const float deceleration);

	void createAnimationComponent(sf::Texture& texture_sheet);

	void createAttributeComponent(const unsigned lvl);

	//Accessors
	virtual const sf::Vector2f& getSpritePosition() const;

	virtual const sf::Vector2f getSpriteCenter() const;

	virtual const sf::Vector2f& getHitboxPosition() const;

	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;

	virtual const sf::FloatRect getSpriteGlobalBounds() const;

	virtual const sf::FloatRect getHitboxGlobalBounds() const;

	virtual const sf::FloatRect getNextPositionBounds(const float& deltaTime) const;

	//Modifiers
	virtual void setPosition(const float x, const float y);

	virtual void loseHp(const int damage);

	virtual void gainHp(const int heal);
	
	//Methods
	virtual void move(const float xDir, const float yDir, const float& deltaTime);

	virtual void stopVelocity();

	virtual void stopVelocityX();

	virtual void stopVelocityY();

	virtual void update(const float& delta_Time) = 0;

	virtual void render(sf::RenderTarget& target, sf::Shader* shader, const bool show_Hitbox) = 0;
};
