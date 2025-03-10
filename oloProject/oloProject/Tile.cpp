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
	this->sprite.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(texture_rect);

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
	return this->sprite.getPosition();
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->sprite.getTextureRect().left << " " << this->sprite.getTextureRect().top << " " <<
	this->hasCollision << " " << this->type;

	return ss.str();
}

const bool Tile::isIntersecting(const sf::FloatRect bounds) const
{
	return this->sprite.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const short& Tile::getType() const
{
	return this->type;
}

//Methods
void Tile::update()
{

}

void Tile::render(
	sf::RenderTarget& target, 
	sf::Shader* shader, 
	const sf::Vector2f playerPosition
	)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);

		shader->setUniform("lightPos", playerPosition);

		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}
}
