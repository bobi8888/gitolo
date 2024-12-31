#include "stdafx.h"

#include "AnimationComponent.h"

//Constructors & Destructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:Sprite(sprite), TextureSheet(textureSheet), LastAnimation(NULL), PriorityAnimation(NULL)
{
	
}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->AnimationSheets)
	{
		delete i.second;
	}
}

//Accessor Methods
const bool& AnimationComponent::getIsDone(const std::string key) 
{
	return this->AnimationSheets[key]->IsDone;
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

const bool& AnimationComponent::play(const std::string key, const float& deltaTime, const bool priority)
{
	if (this->PriorityAnimation)
	{
		if (this->PriorityAnimation = this->AnimationSheets[key])
		{
			if (this->LastAnimation != this->AnimationSheets[key])
			{
				if (this->LastAnimation == NULL)
					this->LastAnimation = this->AnimationSheets[key];
				else
				{
					this->LastAnimation->reset();
					this->LastAnimation = this->AnimationSheets[key];
				}
			}

			this->AnimationSheets[key]->play(deltaTime);
		}
	}
	else //Play animation if there is no priority animation set
	{
		if (priority)
		{
			this->PriorityAnimation = this->AnimationSheets[key];
		}

		if (this->LastAnimation != this->AnimationSheets[key])
		{
			if (this->LastAnimation == NULL)
				this->LastAnimation = this->AnimationSheets[key];
			else
			{
				this->LastAnimation->reset();
				this->LastAnimation = this->AnimationSheets[key];
			}
		}

		this->AnimationSheets[key]->play(deltaTime);
	}

	return this->AnimationSheets[key]->IsDone;
}


const bool& AnimationComponent::play(const std::string key, const float& deltaTime, const float& modifier, const float& modifier_max)
{
	if (this->PriorityAnimation)
	{
		if (this->PriorityAnimation = this->AnimationSheets[key])
		{
			if (this->LastAnimation != this->AnimationSheets[key])
			{
				if (this->LastAnimation == NULL)
					this->LastAnimation = this->AnimationSheets[key];
				else
				{
					this->LastAnimation->reset();
					this->LastAnimation = this->AnimationSheets[key];
				}
			}
			//if the priority animation is done, set priorityAnimation to NULL
			if (this->AnimationSheets[key]->play(deltaTime))
			{
				this->PriorityAnimation = NULL;
			}
		}
	}
	else //Play animation if there is no priority animation set
	{
		if (this->LastAnimation != this->AnimationSheets[key])
		{
			if (this->LastAnimation == NULL)
				this->LastAnimation = this->AnimationSheets[key];
			else
			{
				this->LastAnimation->reset();
				this->LastAnimation = this->AnimationSheets[key];
			}
		}
	}

	if (this->AnimationSheets[key]->play(deltaTime, abs(modifier / modifier_max)))
	{
		this->PriorityAnimation = NULL;
	}

	return this->AnimationSheets[key]->IsDone;
}
