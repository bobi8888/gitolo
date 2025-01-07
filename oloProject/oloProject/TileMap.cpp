#include "stdafx.h"

#include "TileMap.h"
//Constructors & Destructor

TileMap::TileMap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 10;
	this->maxSize.y = 10;
	this->layers = 1;

	this->tileVectors.resize(this->maxSize.x);

	for (size_t i = 0; i < this->maxSize.x; i++)
	{
		this->tileVectors.push_back(std::vector<std::vector<Tile>> ());

		for (size_t j = 0; j < this->maxSize.y; j++)
		{
			this->tileVectors[i].resize(this->maxSize.y);
			this->tileVectors[i].push_back(std::vector<Tile> ());

			for (size_t k = 0; k < this->layers; k++)
			{
				this->tileVectors[i][j].resize(this->layers);
				this->tileVectors[i][j].push_back(Tile(i * this->gridSizeF, j * this->gridSizeF, this->gridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{

}

//Methods

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->tileVectors)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}
