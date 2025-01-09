#include "stdafx.h"

#include "TileMap.h"
//Constructors & Destructor

TileMap::TileMap(
	float gridSize, 
	unsigned width, 
	unsigned height, 
	const sf::IntRect texture_rect,
	std::string texture_file_name
	) : texture_file_name(texture_file_name)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->tileVectors.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

	for (size_t i = 0; i < this->maxSize.x; i++)
	{
		for (size_t j = 0; j < this->maxSize.y; j++)
		{
			this->tileVectors[i].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t k = 0; k < this->layers; k++)
			{
				this->tileVectors[i][j].resize(this->layers, nullptr);
			}
		}
	}

	if (!this->tileTextureSheet.loadFromFile(texture_file_name))

		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TEXTURE SHEET" << texture_file_name << "\n";
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

//Accessors

const sf::Texture* TileMap::getTileTextureSheet() const
{
	return &this->tileTextureSheet;
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

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
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
				this->gridSizeF, 
				this->tileTextureSheet, 
				texture_rect
			);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
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
		if (this->tileVectors[x][y][z] != nullptr)
		{
			//Ok to remove tile
			delete this->tileVectors[x][y][z];

			this->tileVectors[x][y][z] = nullptr;
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text-file.
	Format:
	Size X y
	gridSize
	layers
	texture file name

	All tiles:
	gridPosition x y of all tiles
	textureRext x y is this from the editorState? rename?
	type
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file 
			<< this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->texture_file_name << "\n";

			for (size_t i = 0; i < this->maxSize.x; i++)
			{
				for (size_t j = 0; j < this->maxSize.y; j++)
				{
					for (size_t k = 0; k < this->layers; k++)
					{
						out_file << 1 << 2 << 3 << 8 << 7 << " ";
						//out_file << this->tileVectors[i][j][k];
					}
				}
			}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO :: FILENAME:" << file_name <<"\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	
}
