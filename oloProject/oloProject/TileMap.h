#pragma once

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	void clearTileVectors();

	float gridSizeF;
	int gridSizeI;

	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;

	int layers;

	std::vector<std::vector<std::vector<std::vector<Tile*>>>> tileVectors;

	sf::Texture tileTextureSheet;

	std::string texture_file_name;

	sf::RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	//Constructors & Destructor
	TileMap(
		float gridSize, 
		int width, int height, 
		const sf::IntRect texture_rect,
		std::string texture_file_name
	);

	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileTextureSheet()const ;

	//Methods
	void update();

	void render(sf::RenderTarget& target, Entity* entity = nullptr);

	void addTile(
		const int x, const int y,	const int z, 
		const sf::IntRect& texture_rect,
		const bool& collision, const short& type
	);

	void removeTile(const int x, const int y, const int z);

	void saveToFile(const std::string file_name);

	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& deltaTime);
};

