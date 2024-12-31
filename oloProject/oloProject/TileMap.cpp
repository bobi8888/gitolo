#include "stdafx.h"

#include "TileMap.h"
//Constructors & Destructor

TileMap::TileMap()
{
	this->GridSizeF = 50.f;
	this->GridSizeU = static_cast<unsigned>(this->GridSizeF);
	this->MaxSize.x = 10;
	this->MaxSize.y = 10;
	this->Layers = 1;

	this->TileVectors.resize(this->MaxSize.x);

	for (size_t i = 0; i < this->MaxSize.x; i++)
	{
		this->TileVectors.push_back(std::vector<std::vector<Tile>> ());

		for (size_t j = 0; j < this->MaxSize.y; j++)
		{
			this->TileVectors[i].resize(this->MaxSize.y);
			this->TileVectors[i].push_back(std::vector<Tile> ());

			for (size_t k = 0; k < this->Layers; k++)
			{
				this->TileVectors[i][j].resize(this->Layers);
				this->TileVectors[i][j].push_back(Tile(i * this->GridSizeF, j * this->GridSizeF, this->GridSizeF));
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
	for (auto& x : this->TileVectors)
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

