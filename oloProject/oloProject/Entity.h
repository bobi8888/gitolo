#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/OpenGL.hpp>

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

class Entity
{
private:

protected:
	sf::RectangleShape Rectangle;
	float moveSpeed;

public:
	//Constructors & Destructors
	Entity();
	virtual ~Entity();

	//Methods
	virtual void move(const float& deltaTime, const float xDir, const float yDir);
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);
};

