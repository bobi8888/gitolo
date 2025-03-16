#pragma once

//sf::Drawable;
//sf::Transformable;

struct Particle {
	sf::Vector2f velo;
	sf::Time lifetime;
};

class ParticleBurst
	: public sf::Drawable, public sf::Transformable
{
private:
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Time lifetime;
	int minAngle;
	int maxAngle;
	
	virtual void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states
	) const override;

	void resetParticle(std::size_t index);

public:
	//Constructors & Destructor
	ParticleBurst(unsigned int count, int minAng, int maxAng);
	
	~ParticleBurst();

	//Methods
	void update(sf::Time elapsed);
};

