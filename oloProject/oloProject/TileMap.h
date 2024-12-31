#pragma once

#include "Tile.h"

class TileMap
{
private:
	float GridSizeF;
	unsigned GridSizeU;
	sf::Vector2u MaxSize;
	unsigned Layers;
	std::vector<std::vector<std::vector<Tile>>> TileVectors;

public:
	//Constructors & Destructor
	TileMap();
	virtual ~TileMap();

	//Methods
	void update();
	void render(sf::RenderTarget& target);
};

