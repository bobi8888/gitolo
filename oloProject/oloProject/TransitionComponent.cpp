#include "stdafx.h"
#include "TransitionComponent.h"

TransitionComponent::TransitionComponent()
{
	
}

TransitionComponent::~TransitionComponent()
{

}

//Methods
void TransitionComponent::addTransitionZone(
	const std::string key,
	float xPos, float yPos,
	float width, float height
	)
{
	this->transitions[key] = new TransitionZone(
		xPos, yPos,
		width, height
	);
}

bool TransitionComponent::isZoneActivated(const sf::FloatRect& playerHitbox)
{
	for (const auto& zone : transitions) {
		if (zone.second->isIntersecting(playerHitbox) && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			return true;
		}
	}

	return false;
}

void TransitionComponent::update(const sf::FloatRect& playerHitbox)
{

}

void TransitionComponent::render(sf::RenderTarget& target)
{
	for (const auto& zone : transitions) {
		target.draw(zone.second->hitbox);
	}
}
