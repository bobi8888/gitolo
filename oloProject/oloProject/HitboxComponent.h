#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class HitboxComponent
{
private:
	sf::Sprite& Sprite;
	sf::RectangleShape Hitbox;
	float OffsetX;
	float OffsetY;

public:
	//Constructors & Destructor
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height
	);
	virtual ~HitboxComponent();

	//Methods
	bool isIntersecting(const sf::FloatRect& rect);
	void update();
	void render(sf::RenderTarget& target);
};
