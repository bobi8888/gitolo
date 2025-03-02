#pragma once

class AnimationComponent
{
private:

	class Animation
	{
		public:
			//Variables
			sf::Sprite& sprite;
			sf::Texture& textureSheet;

			sf::IntRect startRect;
			sf::IntRect currentRect;
			sf::IntRect endRect
			;
			int textureWidth;
			int textureHeight;

			float animationTimer;
			float timer;

			bool isDone;

			//Constructors & Destructors
			Animation(
				sf::Sprite& sprite, sf::Texture& texture_sheet,
				float animation_timer, 
				int start_frame_x, int start_frame_y, 
				int frames_x, int frames_y, 
				int width, int height
				)	: sprite(sprite), textureSheet(texture_sheet), 
						animationTimer(animation_timer), 
						textureWidth(width), textureHeight(height),
						timer(0.f), isDone(false)
			{
				this->timer = 0.f;

				this->startRect = sf::IntRect(
					start_frame_x * width, 
					start_frame_y * height, 
					width, height
				);

				this->currentRect = this->startRect;

				this->endRect = sf::IntRect(
					frames_x * width, 
					frames_y * height, 
					width, height
				);

				this->sprite.setTexture(this->textureSheet, true);

				this->sprite.setTextureRect(this->startRect);
			}

			~Animation()
			{
			}

			//Accessor Methods
			//const bool& getIsDone() const
			//{
			//	return IsDone;
			//}

			//Methods
			//Update Timer
			const bool& play(const float& deltaTime)
			{
				//Update Timer
				this->isDone = false;

				this->timer += 100.f * deltaTime;

				if (this->timer >= this->animationTimer)
				{
					//Reset Timer
					this->timer = 0.f;

					//Animate
					if (this->currentRect != this->endRect)
					{
						this->currentRect.left += this->textureWidth;
					}
					else //Reset
					{
						this->currentRect.left = this->startRect.left;

						this->isDone = true;
					}

					this->sprite.setTextureRect(this->currentRect);
				}

				return this->isDone;
			}

			//Update Timer with modifier percentage
			const bool& play(const float& deltaTime, float modifier)
			{
				//Update Timer
				this->isDone = false;

				if (modifier < 0.5f)
					modifier = 0.5f;

				this->timer += modifier * 100.f * deltaTime;

				if (this->timer >= this->animationTimer)
				{
					//Reset Timer
					this->timer = 0.f;

					//Animate
					if (this->currentRect != this->endRect)
					{
						this->currentRect.left  += this->textureWidth;
					}
					else //Reset
					{
						this->currentRect.left = this->startRect.left;

						this->isDone = true;
					}

					this->sprite.setTextureRect(this->currentRect);
				}

				return this->isDone;
			}

			void reset()
			{
				this->currentRect = this->startRect;

				this->timer = this->animationTimer;
			}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animationSheets;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	//Constructors & Destructors
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	//Accessor Methods
	const bool& getIsDone(const std::string key);

	//Methods
	/*
	animation_timer: Lower value means faster loop through sprite sheet
	start_frame_x: Index of the X position (left side of sprite)
	start_frame_y: Index of the Y position (top of sprite)
	frames_x: Index number of animations in the X direction for EndRect
	frames_y: Index number of starting Y position for EndRect
	width: width in pixles of each animation
	height: height in pixles of each animation
	*/
	void addAnimation(
		const std::string key, float animation_Timer,
		int start_frame_x, int start_frame_y, 
		int frames_x, int frames_y,
		int width, int height
	);

	//void startAnimation(const std::string animation);
	//void pauseAnimation(const std::string animation);
	//void resetAnimation(const std::string animation);

	const bool& play(const std::string key, const float& deltaTime, const bool priority = false);

	//Play with modifier...write a better explaination
	const bool& play(const std::string key, const float& deltaTime, const float& modifier, const float& modifier_max);
};

