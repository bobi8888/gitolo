#include "stdafx.h"

#include "TileMap.h"
//Constructors & Destructor

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->tileVectors.resize(this->maxSize.x);

	for (size_t i = 0; i < this->maxSize.x; i++)
	{
		this->tileVectors.push_back(std::vector<std::vector<Tile*>> ());

		for (size_t j = 0; j < this->maxSize.y; j++)
		{
			this->tileVectors[i].resize(this->maxSize.y);
			this->tileVectors[i].push_back(std::vector<Tile*> ());

			for (size_t k = 0; k < this->layers; k++)
			{
				this->tileVectors[i][j].resize(this->layers);
				this->tileVectors[i][j].push_back(nullptr);
			}
		}
	}
}

TileMap::~TileMap()
{
	for (size_t i = 0; i < this->maxSize.x; i++)
	{
		for (size_t j = 0; j < this->maxSize.y; j++)
		{
			for (size_t k = 0; k < this->layers; k++)
			{
				delete this->tileVectors[i][j][k];

			}
		}
	}
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
			for (auto *z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (
		x < this->maxSize.x && 
		x >= 0 &&

		y < this->maxSize.y && 
		y >= 0 &&

		z < this->layers &&
		z >= 0
		)
	{
		if (this->tileVectors[x][y][z] == nullptr)
		{
		//Ok to add tile
			this->tileVectors[x][y][z] = new Tile(
				x * this->gridSizeF, 
				y * this->gridSizeF, 
				this->gridSizeF
			);
		}
	}
}

void TileMap::removeTile()
{

}
