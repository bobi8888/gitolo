#pragma once

enum TileTypes {
	DEFAULT = 0, 
	WOOD = 1, 
	GRAVEL = 2, 
	METAL = 3, 
	SAND = 4, 
	ABOVE_BRUSH = 5
};

class Tile
{
private:

protected:
	sf::Sprite sprite;
	bool hasCollision;
	short type;

public:
	//Constructors & Destructor
	//Tile();
	Tile(
		int grid_x, int grid_y, float gridSizeF, 
		const sf::Texture& texture, 
		const sf::IntRect& texture_rect,
		bool collision, short type
	);

	virtual ~Tile();

	//Accessors
	const bool& getCollision() const;

	const sf::Vector2f& getPosition() const;

	const std::string getAsString() const;

	const bool isIntersecting(const sf::FloatRect bounds) const;

	const sf::FloatRect getGlobalBounds() const;

	const short& getType() const;

	//Methods
	void update();

	void render(
		sf::RenderTarget& target, 
		sf::Shader* shader = NULL, 
		const sf::Vector2f playerPosition = sf::Vector2f()
	);
};

