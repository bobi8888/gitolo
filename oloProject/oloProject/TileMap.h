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
	sf::RectangleShape collisionBox;
	//add deferredBox to indicate defered tiles?

	int layers;

	std::vector<std::vector<std::vector<std::vector<Tile*>>>> tileVectors;

	sf::Texture tileTextureSheet;

	std::string texture_file_name;

	std::stack<Tile*> deferredRenderedStack;

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

	TileMap(const std::string file_name);

	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileTextureSheet()const ;

	const int getLayerSize(const sf::Vector2i mousePos, const int z) const;

	const sf::Vector2i& getGridMaxSizeInt() const;

	const sf::Vector2f& getGridMaxSizeFloat() const;


	//Methods
	void addTile(
		const int x, const int y,	const int z, 
		const sf::IntRect& texture_rect,
		const bool& collision, const short& type
	);

	void removeTile(const int x, const int y, const int z);

	void saveToFile(const std::string file_name);

	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& deltaTime);

	void render(
		sf::RenderTarget& target, 
		const sf::Vector2i& gridPosition,
		sf::Shader* shader = NULL, 
		const sf::Vector2f playerPosition = sf::Vector2f(),
		const bool show_hitbox = false
	);

	void renderDeferred(
		sf::RenderTarget& target, 
		sf::Shader* shader = NULL, 
		const sf::Vector2f playerPosition = sf::Vector2f()
	);
};

