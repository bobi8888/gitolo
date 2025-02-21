#include "stdafx.h"

#include "Tile.h"

//Constructors & Destructor
//Tile::Tile(){}

Tile::Tile(
	int grid_x, int grid_y, float gridSizeF, 
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

//Accessors
const bool& Tile::getCollision() const
{
	return hasCollision;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->tileShape.getPosition();
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->tileShape.getTextureRect().left << " " << this->tileShape.getTextureRect().top << " " <<
	this->hasCollision << " " << this->type;

	return ss.str();
}

const bool Tile::isIntersecting(const sf::FloatRect bounds) const
{
	return this->tileShape.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->tileShape.getGlobalBounds();
}

const short& Tile::getType() const
{
	return this->type;
}

//Methods
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);

		shader->setUniform("lightPos", player_position);

		target.draw(this->tileShape, shader);
	}
	else
	{
		target.draw(this->tileShape);
	}
}
