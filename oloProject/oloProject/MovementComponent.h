#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/OpenGL.hpp>

//#include<iostream>
#include<fstream>
#include<sstream>
//#include<vector>
#include<stack>
//#include<map>

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
	//Methods
	const bool isIdle() const;
	void move(const float xDir, const float yDir, const float& deltaTime);
	void update(const float &deltaTime);
};

