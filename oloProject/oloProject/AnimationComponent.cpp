#include "AnimationComponent.h"

//Constructors & Destructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:Sprite(sprite), TextureSheet(textureSheet)
{
	
}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->AnimationSheets)
	{
		delete i.second;
	}
}



//Methods
void AnimationComponent::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y,
	int width, int height)
{
	this->AnimationSheets[key] = new Animation(
		this->Sprite, this->TextureSheet,
		animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height		
		);
}

void AnimationComponent::startAnimation(const std::string animation)
{
}

void AnimationComponent::pauseAnimation(const std::string animation)
{
}

void AnimationComponent::resetAnimation(const std::string animation)
{
}

void AnimationComponent::play(const std::string key, const float& deltaTime)
{
	this->AnimationSheets[key]->play(deltaTime);
}
