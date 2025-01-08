#pragma once

class Tile
{
private:

protected:
	sf::RectangleShape tileShape;

public:
	//Constructors & Destructor
	Tile();
	Tile(
		float x, 
		float y, 
		float gridSizeF, 
		const sf::Texture& texture, 
		const sf::IntRect& texture_rect
	);
	virtual ~Tile();

	//Methods
	void update();
	void render(sf::RenderTarget& target);
};

