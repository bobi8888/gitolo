#include "stdafx.h"
#include "ParticleBurst.h"

void ParticleBurst::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(vertices, states);
}

void ParticleBurst::resetParticle(std::size_t index)
{
	/*This makes the particles expel out in a circle
	spreadAngle controls the overall area the particals will go
	*/
	float randomFactor = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	
	float angleDeg = minAngle + randomFactor * (maxAngle - minAngle);

	float angle = angleDeg * 3.14159265f / -180.f;

	float speed = 50.f + std::rand() % 50;

	particles[index].velo = sf::Vector2f(
		std::cos(angle) * speed,
		std::sin(angle) * speed
	);

	particles[index].lifetime = lifetime;
	vertices[index].position = sf::Vector2f(0.f, 0.f);
	vertices[index].color = sf::Color::White;
}

//Constructors & Destructor
ParticleBurst::ParticleBurst(unsigned int count, int minAng, int maxAng)
	: particles(count),
	vertices(sf::Points, count),
	lifetime(sf::seconds(3.f)),
	minAngle(minAng),
	maxAngle(maxAng)
{
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		resetParticle(i);
	}
}

ParticleBurst::~ParticleBurst()
{

}

//Methods
void ParticleBurst::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		Particle& p = particles[i];
		p.lifetime -= elapsed;

		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i);

		vertices[i].position += p.velo * elapsed.asSeconds();

		float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
		vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}
