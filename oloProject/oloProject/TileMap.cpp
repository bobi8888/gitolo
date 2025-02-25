#include "stdafx.h"

#include "TileMap.h"
//Constructors & Destructor

void TileMap::clearTileVectors()
{
	for (int i = 0; i < this->maxSizeWorldGrid.x; i++)
	{
		for (int j = 0; j < this->maxSizeWorldGrid.y; j++)
		{
			for (int k = 0; k < this->layers; k++)
			{
				for (size_t l = 0; l < this->tileVectors[i][j][k].size(); l++)
				{
					delete this->tileVectors[i][j][k][l];

					//this->tileVectors[i][j][k][l] = nullptr;
				}
				this->tileVectors[i][j][k].clear();

			}
			this->tileVectors[i][j].clear();

		}
		this->tileVectors[i].clear();

	}
	this->tileVectors.clear();

}

TileMap::TileMap(
	float gridSize, 
	int width, int height, 
	const sf::IntRect texture_rect,
	std::string texture_file_name
	) : texture_file_name(texture_file_name)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;

	this->layers = 1;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->tileVectors.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

	for (int i = 0; i < this->maxSizeWorldGrid.x; i++)
	{
		for (int j = 0; j < this->maxSizeWorldGrid.y; j++)
		{
			this->tileVectors[i].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

			for (int k = 0; k < this->layers; k++)
			{
				this->tileVectors[i][j].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileTextureSheet.loadFromFile(texture_file_name))

		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TEXTURE SHEET" << texture_file_name << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
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

const int TileMap::getLayerSize(const sf::Vector2i mousePos, const int z) const
{
	if (mousePos.x >= 0 && mousePos.x < static_cast<int>(this->tileVectors.size()))
	{
		if (mousePos.y >= 0 && mousePos.y < static_cast<int>(this->tileVectors[mousePos.x].size()))
		{
			if (z >= 0 && z < static_cast<int>(this->tileVectors[mousePos.x][mousePos.y].size()))
			{
				return static_cast<int>(
					this->tileVectors[mousePos.x][mousePos.y][layer].size()
				);
			}
		}
	}

	return -1;
}

//Methods
void TileMap::addTile(
	const int x, const int y, const int z, 
	const sf::IntRect& texture_rect, 
	const bool& collision, const short& type
	)
{
	if (
		x < this->maxSizeWorldGrid.x &&
		x >= 0 &&

		y < this->maxSizeWorldGrid.y &&
		y >= 0 &&

		z < this->layers &&
		z >= 0
		)
	{
				//Ok to add tile
		this->tileVectors[x][y][z].push_back(new Tile(
			x, y, this->gridSizeF, 
			this->tileTextureSheet, 
			texture_rect,
			collision, type
			)
		);		
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if (
		x < this->maxSizeWorldGrid.x &&
		x >= 0 &&

		y < this->maxSizeWorldGrid.y &&
		y >= 0 &&

		z < this->layers &&
		z >= 0
		)
	{
		if (!this->tileVectors[x][y][z].empty())
		{
			//Ok to remove tile
			delete this->tileVectors[x][y][z][this->tileVectors[x][y][z].size() - 1];

			this->tileVectors[x][y][z].pop_back();
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
			<< this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->texture_file_name << "\n";

			for (int i = 0; i < this->maxSizeWorldGrid.x; i++)
			{
				for (int j = 0; j < this->maxSizeWorldGrid.y; j++)
				{
					for (int k = 0; k < this->layers; k++)
					{
						if (!this->tileVectors[i][j][k].empty())
						{
							for (size_t l = 0; l < this->tileVectors[i][j][k].size(); l++)
							{
								out_file << i << " " << j << " " << k << " " <<
									this->tileVectors[i][j][k][l]->getAsString() << "\n";
							}
						}

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
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file_name = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int texture_x = 0;
		int texture_y = 0;
		int texture_z = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file_name;
	
		if (size.x != maxSizeWorldGrid.x)
			std::cout << "ERROR::SIZE.X IN editorTileMap != maxSizeWorldGrid.x" << "\n";

		if (size.y != maxSizeWorldGrid.y)
			std::cout << "ERROR::SIZE.Y IN editorTileMap != maxSizeWorldGrid.y" << "\n";

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->texture_file_name = texture_file_name;

		this->clearTileVectors();

		this->tileVectors.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());

		for (int i = 0; i < this->maxSizeWorldGrid.x; i++)
		{
			for (int j = 0; j < this->maxSizeWorldGrid.y; j++)
			{
				this->tileVectors[i].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

				for (int k = 0; k < this->layers; k++)
				{
					this->tileVectors[i][j].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileTextureSheet.loadFromFile(texture_file_name))
			std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE :: FILENAME:" << file_name << "\n";


		//Load all tiles
		while (in_file >> x >> y >> z >> texture_x >> texture_y >> collision >> type)
		{
			this->tileVectors[x][y][z].push_back(new Tile(
				x, y, this->gridSizeF, 
				this->tileTextureSheet, 
				sf::IntRect(texture_x, texture_y, this->gridSizeI, this->gridSizeI), 
				collision, type
				)
			);
		}
	}
	else
	{

	}

	in_file.close();
}

void TileMap::updateCollision(Entity* entity, const float& deltaTime)
{
	//World Bounds collision
	if (entity->getHitboxPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getHitboxPosition().y);

		entity->stopVelocityX();
	}
	else if (entity->getHitboxPosition().x + entity->getHitboxGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getHitboxGlobalBounds().width, entity->getHitboxPosition().y);
		
		entity->stopVelocityX();
	}

	if (entity->getHitboxPosition().y < 0.f)
	{
		entity->setPosition(entity->getHitboxPosition().x, 0.f);
		
		entity->stopVelocityY();
	}
	else if (entity->getHitboxPosition().y + entity->getHitboxGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getHitboxPosition().x, this->maxSizeWorldF.y - entity->getHitboxGlobalBounds().height);

		entity->stopVelocityY();
	}		

	//Tile collision
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;

	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 4;

	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;

	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 4;

	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;
	

	for (int i = fromX; i < toX; i++)
	{
		for (int j = this->fromY; j < this->toY; j++)
		{
			for (size_t k = 0; k < this->tileVectors[i][j][this->layer].size(); k++)
			{			
				if (this->tileVectors[i][j][this->layer][k] != nullptr)
				{
					sf::FloatRect playerBounds = entity->getHitboxGlobalBounds();

					sf::FloatRect wallBounds = this->tileVectors[i][j][this->layer][k]->getGlobalBounds();

					sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(deltaTime);

					if (this->tileVectors[i][j][this->layer][k]->getCollision()
						&& this->tileVectors[i][j][this->layer][k]->isIntersecting(nextPositionBounds)
						)
					{
						//Bottom of tile Collision
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left
							)
						{
							entity->stopVelocityY();

							entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						}

						//Top of tile Collision
						if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left
							)
						{
							entity->stopVelocityY();

							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}

						//Right of tile Collision
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top
							)
						{
							entity->stopVelocityX();

							entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}

						//Left of tile Collision
						if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top
							)
						{
							entity->stopVelocityX();

							entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		}
	}
}

void TileMap::render(
	sf::RenderTarget& target, 
	const sf::Vector2i& gridPosition,
	sf::Shader* shader,
	const sf::Vector2f playerPosition,
	const bool show_hitbox
	)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 12;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = gridPosition.x + 13;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = gridPosition.y - 9;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = gridPosition.y + 11;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;


	for (int x = this->fromX; x < this->toX; x++)
	{
		//std::cout << "x: " << x << "\n";
		for (int y = this->fromY; y < this->toY; y++)
		{
			//std::cout << "y: " << y << "\n";

			for (size_t k = 0; k < this->tileVectors[x][y][this->layer].size(); k++)
			{
				//std::cout << "k: " << k << "\n";

				if (this->tileVectors[x][y][this->layer][k]->getType() == TileTypes::ABOVE_BRUSH)
				{
					this->deferredRenderedStack.push(this->tileVectors[x][y][this->layer][k]);
				}
				else
				{
					if(shader)
						this->tileVectors[x][y][this->layer][k]->render(target, shader, playerPosition);
					else
						this->tileVectors[x][y][this->layer][k]->render(target);
				}


				if (show_hitbox)
				{
					if (this->tileVectors[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->tileVectors[x][y][this->layer][k]->getPosition());

						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target,sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->deferredRenderedStack.empty())
	{
		if (shader)
			deferredRenderedStack.top()->render(target, shader, playerPosition);
		else
			deferredRenderedStack.top()->render(target);

		deferredRenderedStack.pop();
	}
}
