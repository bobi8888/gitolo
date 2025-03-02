#pragma once

class sf::Sprite;
class sf::RectangleShape;

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

	float xOffset;
	float yOffset;

public:
	//Constructors & Destructor
	HitboxComponent(
		sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height
	);

	virtual ~HitboxComponent();

	//Accessors 
	const sf::Vector2f& getPosition();

	const sf::FloatRect getGlobalBounds() const;

	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);

	void setPosition(const float& x, const float& y);

	//Methods
	bool isIntersecting(const sf::FloatRect& rect);

	void update();

	void render(sf::RenderTarget& target);
};
