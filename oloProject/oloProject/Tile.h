#pragma once

class Tile
{
private:

protected:
	sf::RectangleShape tileShape;
	sf::Texture* texture;

public:
	//Constructors & Destructor
	Tile();
	Tile(float x, float y, float gridSizeF);
	virtual ~Tile();

	//Methods
	void update();
	void render(sf::RenderTarget& target);
};

