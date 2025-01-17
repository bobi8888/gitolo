#include "stdafx.h"

#include "TileMap.h"
//Constructors & Destructor

void TileMap::clearTileVectors()
{
	for (size_t i = 0; i < this->maxSize.x; i++)
	{
		for (size_t j = 0; j < this->maxSize.y; j++)
		{
			for (size_t k = 0; k < this->layers; k++)
			{
				delete this->tileVectors[i][j][k];

				this->tileVectors[i][j][k] = nullptr;
			}

			this->tileVectors[i][j].clear();
		}

		this->tileVectors[i].clear();
	}

	this->tileVectors.clear();

}

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
	this->clearTileVectors();
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

void TileMap::addTile(
	const unsigned x, const unsigned y, const unsigned z, 
	const sf::IntRect& texture_rect, 
	const bool& collision, const short& type
	)
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
				x, y, this->gridSizeF, 
				this->tileTextureSheet, 
				texture_rect,
				collision, type
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
	gridPosition x y layer of all tiles
	textureRext x y is this from the editorState? rename?
	collision
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
						if (this->tileVectors[i][j][k])
							out_file << i << " " << j << " " << k << " " << this->tileVectors[i][j][k]->getAsString() << "\n";
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
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file_name = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned texture_x = 0;
		unsigned texture_y = 0;
		unsigned texture_z = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file_name;
	
		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->texture_file_name = texture_file_name;

		this->clearTileVectors();

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
			std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE :: FILENAME:" << file_name << "\n";


		//Load all tiles
		while (in_file >> x >> y >> z >> texture_x >> texture_y >> collision >> type)
		{
			this->tileVectors[x][y][z] = new Tile(
				x, y, this->gridSizeF, 
				this->tileTextureSheet, 
				sf::IntRect(texture_x, texture_y, this->gridSizeU, this->gridSizeU), 
				collision, type
				);
		}
	}
	else
	{

	}

	in_file.close();
}
