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
	unsigned gridSizeU;
	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> tileVectors;
	sf::Texture tileTextureSheet;
	std::string texture_file_name;

	sf::RectangleShape collisionBox;

public:
	//Constructors & Destructor
	TileMap(
		float gridSize, 
		unsigned width, 
		unsigned height, 
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
		const unsigned x, const unsigned y,	const unsigned z, 
		const sf::IntRect& texture_rect,
		const bool& collision, const short& type
	);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity);
};

