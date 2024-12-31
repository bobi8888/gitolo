#include "stdafx.h"

#include "Tile.h"

//Constructors & Destructor

Tile::Tile(){}

Tile::Tile(float x, float y, float gridSizeF)
{
	//this->Texture->loadFromFile("Resources/Images/Tiles/gravel.png");

	this->TileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->TileShape.setFillColor(sf::Color::Yellow);
	this->TileShape.setOutlineColor(sf::Color::Blue);
	this->TileShape.setOutlineThickness(1.5f);
	this->TileShape.setPosition(x, y);
	//this->TileShape.setTexture(Texture);
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
	target.draw(this->TileShape);
}
