#pragma once

struct TrickleParticle {
	sf::Vector2f position;
	sf::Vector2f velo;
	sf::Time lifetime;
	sf::Time initLifetime; //max lifetime?
};
class ParticleTrickle
	: public sf::Drawable, public sf::Transformable
{
private:
	std::vector<TrickleParticle> particles;
	sf::VertexArray vertices;
	sf::Texture texture;
	float minAngle, maxAngle;
	sf::Time minLifetime, maxLifetime;
	float texturePixelSize;
	float speedMin;
	int speedMax;
	
//private methods
	virtual void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states
	) const override;

	void resetParticle(std::size_t index);

public:
//Constructors & Deconstructor
	explicit ParticleTrickle (
		const std::string& textureFile, unsigned int count,
		float speedMin = 1.f, int speedMax = 5,
		float minAngle = 0.f, float maxAngle = 360.f,
		sf::Time minLifetime = sf::seconds(1.5f),
		sf::Time maxLifetime = sf::seconds(5.f)
		);

//Methods
	void update(sf::Time elapsed);
};

