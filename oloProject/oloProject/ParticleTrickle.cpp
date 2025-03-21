#include "stdafx.h"
#include "ParticleTrickle.h"

//private methods
void ParticleTrickle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply the transformation.
    states.transform *= getTransform();
    states.texture = &texture;
    target.draw(vertices, states);
}

void ParticleTrickle::resetParticle(std::size_t i)
{
    // Generate a random factor between 0 and 1.
    float randomFactor = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

    // Calculate a random angle (in degrees) in the [m_minAngle, m_maxAngle] range.
    float angleDeg = minAngle + randomFactor * (maxAngle - minAngle);
    float angle = angleDeg * 3.14159265f / 180.f;

    float speed = speedMin + std::rand() % speedMax;

    particles[i].position = sf::Vector2f(0.f, 0.f);

    particles[i].velo = sf::Vector2f(
        std::cos(angle) * speed,
        std::sin(angle) * speed
    );

    // Generate another random factor for the particle's lifetime.
    randomFactor = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

    float lifetimeSeconds = 
        minLifetime.asSeconds() 
        + randomFactor 
        * (maxLifetime.asSeconds() - minLifetime.asSeconds()
    );

    sf::Time randomLifetime = sf::seconds(lifetimeSeconds);

    particles[i].lifetime = randomLifetime;
    particles[i].initLifetime = randomLifetime;

    vertices[i].position = sf::Vector2f(0.f, 0.f);

    // Also update the quad for this particle.
    std::size_t index = i * 4;
    float halfSize = texturePixelSize / 2.f;
    sf::Vector2f pos = particles[i].position;
    vertices[index + 0].position = pos + sf::Vector2f(-halfSize, -halfSize);
    vertices[index + 1].position = pos + sf::Vector2f(halfSize, -halfSize);
    vertices[index + 2].position = pos + sf::Vector2f(halfSize, halfSize);
    vertices[index + 3].position = pos + sf::Vector2f(-halfSize, halfSize);

    // Set texture coordinates.
    sf::Vector2u texSize = texture.getSize();
    vertices[index + static_cast<size_t>(0)].texCoords = sf::Vector2f(0.f, 0.f);
    vertices[index + static_cast<size_t>(1)].texCoords = sf::Vector2f(static_cast<float>(texSize.x), 0.f);
    vertices[index + static_cast<size_t>(2)].texCoords = sf::Vector2f(texSize.x, texSize.y);
    vertices[index + static_cast<size_t>(3)].texCoords = sf::Vector2f(0.f, texSize.y);

    // Set initial color to white (full opacity).
    vertices[index + 0].color = sf::Color::White;
    vertices[index + 1].color = sf::Color::White;
    vertices[index + 2].color = sf::Color::White;
    vertices[index + 3].color = sf::Color::White;
}

//Constructors & Deconstructor

ParticleTrickle::ParticleTrickle(){}

ParticleTrickle::ParticleTrickle(
    const std::string& textureFile,	unsigned int count, 
	float speedMin,int speedMax,
    float minAngle, float maxAngle, 
	sf::Time minLifetime, sf::Time maxLifetime
	) : particles(count),
        texturePixelSize(16.f),
        vertices(sf::Quads, count * 4),
        speedMin(speedMin), speedMax(speedMax),
        minAngle(minAngle), maxAngle(maxAngle),
        minLifetime(minLifetime), maxLifetime(maxLifetime)
   
{
    if (!texture.loadFromFile(textureFile))
        std::cout << "ERROR::PARTICLETRICKLE::COULD NOT LOAD TEXTURE FILE" << "\n";
        
    for (std::size_t i = 0; i < particles.size(); ++i)
        resetParticle(i);
}

//Methods
void ParticleTrickle::update(sf::Time elapsed)
{    
    for (std::size_t i = 0; i < particles.size(); ++i) {

        TrickleParticle& p = particles[i];

        p.lifetime -= elapsed;

        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);
           
        // Update the particle's position.
        p.position += p.velo * elapsed.asSeconds();

        //used for individual particles
        //vertices[i].position += p.velo * elapsed.asSeconds();
        
        // Fade the particle based on its remaining lifetime.
        float ratio = p.lifetime.asSeconds() / p.initLifetime.asSeconds();
       // ratio < 0.5f ? ratio = 0.5f : ratio;

        std::size_t index = i * 4;

        float halfSize = texturePixelSize / 2.f;

        // Update positions for a quad centered at p.position.
        vertices[index + 0].position = p.position + sf::Vector2f(-halfSize, -halfSize);
        vertices[index + 1].position = p.position + sf::Vector2f(halfSize, -halfSize);
        vertices[index + 2].position = p.position + sf::Vector2f(halfSize, halfSize);
        vertices[index + 3].position = p.position + sf::Vector2f(-halfSize, halfSize);

        // Set texture coordinates based on the entire texture.
        sf::Vector2u texSize = texture.getSize();
        vertices[index + 0].texCoords = sf::Vector2f(0.f, 0.f);
        vertices[index + 1].texCoords = sf::Vector2f(static_cast<float>(texSize.x), 0.f);
        vertices[index + 2].texCoords = sf::Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y));
        vertices[index + 3].texCoords = sf::Vector2f(0.f, static_cast<float>(texSize.y));

        // Apply fading to the particle color.
        sf::Color col = sf::Color::White;
        col.a = static_cast<sf::Uint8>(ratio * 255);
        vertices[index + 0].color = col;
        vertices[index + 1].color = col;
        vertices[index + 2].color = col;
        vertices[index + 3].color = col;

        //used for individual particles
        //vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}
