#pragma once

enum TileTypes {DEFAULT = 0, WOOD, GRAVEL, METAL, SAND};

class Tile
{
private:

protected:
	sf::RectangleShape tileShape;
	bool hasCollision;
	short type;

public:
	//Constructors & Destructor
	Tile();
	Tile(
		unsigned grid_x, unsigned grid_y, float gridSizeF, 
		const sf::Texture& texture, 
		const sf::IntRect& texture_rect,
		bool collision, short type
	);

	virtual ~Tile();

	//Accessors
	const bool& getCollision() const;

	const sf::Vector2f& getPosition() const;

	const std::string getAsString() const;

	//Methods
	void update();

	void render(sf::RenderTarget& target);
};

