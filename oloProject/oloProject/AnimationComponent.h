#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>

#include<map>

class AnimationComponent
{
private:

	class Animation
	{
		public:
			//Variables
			sf::Sprite& Sprite;
			sf::Texture& TextureSheet;
			float AnimationTimer;
			float Timer;
			int TextureWidth;
			int TextureHeight;
			sf::IntRect StartRect;
			sf::IntRect CurrentRect;
			sf::IntRect EndRect;

			//Constructors & Destructors
			Animation(
				sf::Sprite& sprite, sf::Texture& texture_sheet, 
				float animation_timer, 
				int start_frame_x, int start_frame_y, int frames_x, int frames_y, 
				int width, int height)
					: Sprite(sprite), TextureSheet(texture_sheet), AnimationTimer(animation_timer), TextureWidth(width), TextureHeight(height)
			{
				this->Timer = 0.f;
				this->StartRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
				this->CurrentRect = this->StartRect;
				this->EndRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

				this->Sprite.setTexture(this->TextureSheet, true);
				this->Sprite.setTextureRect(this->StartRect);
			}

			~Animation()
			{
			}

			//Methods
			void play(const float& deltaTime)
			{
				//Update Timer
				this->Timer += 100.f * deltaTime;
				if (this->Timer >= this->AnimationTimer)
				{
					//Reset Timer
					this->Timer = 0.f;

					if (this->CurrentRect != this->EndRect)
					{
						this->CurrentRect.left  += this->TextureWidth;
					}
					else
					{
						this->CurrentRect.left = this->StartRect.left;
					}

					this->Sprite.setTextureRect(this->CurrentRect);
				}
			}

			void reset()
			{
				this->CurrentRect = this->StartRect;
				this->Timer = 0.f;
			}
	};

	sf::Sprite& Sprite;
	sf::Texture& TextureSheet;
	std::map<std::string, Animation*> AnimationSheets;

public:
	//Constructors & Destructors
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

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
		const std::string key,
		float animation_Timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y,
		int width, int height);

	void startAnimation(const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);

	void play(const std::string key, const float& deltaTime);
};
