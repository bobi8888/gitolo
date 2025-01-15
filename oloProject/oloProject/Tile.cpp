#include "stdafx.h"

#include "Tile.h"

//Constructors & Destructor

Tile::Tile(){}

Tile::Tile(
	unsigned grid_x, unsigned grid_y, float gridSizeF, 
	const sf::Texture& texture, 
	const sf::IntRect& texture_rect,
	bool collision, short type
	)
{
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	//this->tileShape.setFillColor(sf::Color::Yellow);
	//this->tileShape.setOutlineColor(sf::Color::Blue);
	//this->tileShape.setOutlineThickness(1.5f);
	this->tileShape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->tileShape.setTexture(&texture);
	this->tileShape.setTextureRect(texture_rect);

	this->hasCollision = collision;

	this->type = type;
}

Tile::~Tile()
{

}

//Methods

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->tileShape.getTextureRect().left << " " << this->tileShape.getTextureRect().top << " " << this->hasCollision << 
	" " << this->type;

	return ss.str();
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tileShape);
}
