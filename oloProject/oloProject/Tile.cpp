#include "stdafx.h"

#include "Tile.h"

//Constructors & Destructor

Tile::Tile(){}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileShape.setFillColor(sf::Color::Yellow);
	//this->tileShape.setOutlineColor(sf::Color::Blue);
	//this->tileShape.setOutlineThickness(1.5f);
	this->tileShape.setPosition(x, y);
	this->tileShape.setTexture(&texture);
	this->tileShape.setTextureRect(texture_rect);
}

Tile::~Tile()
{

}

//Methods

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tileShape);
}
