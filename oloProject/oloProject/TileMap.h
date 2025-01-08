#pragma once

#include "Tile.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> tileVectors;
	sf::Texture tileTextureSheet;

public:
	//Constructors & Destructor
	TileMap(
		float gridSize, 
		unsigned width, 
		unsigned height, 
		const sf::IntRect texture_rect
	);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileTextureSheet()const ;

	//Methods
	void update();
	void render(sf::RenderTarget& target);

	void addTile(
		const unsigned x, 
		const unsigned y, 
		const unsigned z, 
		const sf::IntRect& texture_rect
	);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

};

