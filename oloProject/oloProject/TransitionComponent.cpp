#include "stdafx.h"
#include "TransitionComponent.h"

TransitionComponent::TransitionComponent()
{
	
}

TransitionComponent::~TransitionComponent()
{

}

//Methods
void TransitionComponent::render(sf::RenderTarget& target)
{
	for (const auto& zone : transitions) {
		target.draw(zone.second->hitbox);
	}	
}

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
