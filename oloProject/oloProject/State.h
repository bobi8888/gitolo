#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

class State
{
private:
	sf::RenderWindow* Window;
	std::vector<sf::Texture> Textures;	

public:
	State();
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void endState() = 0;

	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};
