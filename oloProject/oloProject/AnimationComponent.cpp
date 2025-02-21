#include "stdafx.h"

#include "AnimationComponent.h"

//Constructors & Destructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet), lastAnimation(NULL), priorityAnimation(NULL)
{
	
}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animationSheets)
	{
		delete i.second;
	}
}

//Accessor Methods
const bool& AnimationComponent::getIsDone(const std::string key) 
{
	return this->animationSheets[key]->isDone;
}

//Methods
void AnimationComponent::addAnimation(
	const std::string key, float animation_timer,
	int start_frame_x, int start_frame_y, 
	int frames_x, int frames_y,
	int width, int height
	)
{
	this->animationSheets[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer, 
		start_frame_x, start_frame_y, 
		frames_x, frames_y, 
		width, height		
	);
}

//void AnimationComponent::startAnimation(const std::string animation)
//{
//}
//
//void AnimationComponent::pauseAnimation(const std::string animation)
//{
//}
//
//void AnimationComponent::resetAnimation(const std::string animation)
//{
//
//}

const bool& AnimationComponent::play(const std::string key, const float& deltaTime, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation = this->animationSheets[key])
		{
			if (this->lastAnimation != this->animationSheets[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animationSheets[key];
				else
				{
					this->lastAnimation->reset();

					this->lastAnimation = this->animationSheets[key];
				}
			}

			this->animationSheets[key]->play(deltaTime);
		}
	}
	else //Play animation if there is no priority animation set
	{
		if (priority)
		{
			this->priorityAnimation = this->animationSheets[key];
		}

		if (this->lastAnimation != this->animationSheets[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animationSheets[key];
			else
			{
				this->lastAnimation->reset();

				this->lastAnimation = this->animationSheets[key];
			}
		}

		this->animationSheets[key]->play(deltaTime);
	}

	return this->animationSheets[key]->isDone;
}

const bool& AnimationComponent::play(
	const std::string key, const float& deltaTime, 
	const float& modifier, const float& modifier_max
	)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation = this->animationSheets[key])
		{
			if (this->lastAnimation != this->animationSheets[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animationSheets[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animationSheets[key];
				}
			}
			//if the priority animation is done, set priorityAnimation to NULL
			if (this->animationSheets[key]->play(deltaTime))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation if there is no priority animation set
	{
		if (this->lastAnimation != this->animationSheets[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animationSheets[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animationSheets[key];
			}
		}
	}

	if (this->animationSheets[key]->play(deltaTime, abs(modifier / modifier_max)))
	{
		this->priorityAnimation = NULL;
	}

	//std::cout << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << "\n";

	return this->animationSheets[key]->isDone;
}
