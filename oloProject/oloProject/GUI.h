#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include<iostream>
#include<vector>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:
		short unsigned ButtonState;

		sf::RectangleShape Rectangle;
		sf::Font* Font;
		sf::Text Text;
	
		sf::Color TextIdleColor;
		sf::Color TextHoverColor;
		sf::Color TextActiveColor;

		sf::Color IdleColor;
		sf::Color HoverColor;
		sf::Color ActiveColor;

	public:	
		Button();
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
		virtual ~Button();

		//Accessors
		const bool isPressed() const;
		const std::string& getText() const;

		//Modifiers
		void setText(const std::string text);

		//Methods
		void update(const sf::Vector2f mousePos);
		void render(sf::RenderTarget& target);

	};

	class DropdownList
	{
		private:
			float Keytime;
			float KeytimeMax;
			sf::Font& ListFont;
			Button* ActiveElement;
			std::vector<Button*> ElementList;
			bool ShowList;

		public:
			//Constructors & Destructor
			DropdownList(float xPos, float yPos, float width, float height, sf::Font& font, std::string list[],unsigned elementsNum, unsigned default_index = 0);
			~DropdownList();

			//Methods
			const bool getKeytime();
			void updateKeytime(const float& deltaTime);
			void update(const sf::Vector2f& mousePos, const float& deltaTime);
			void render(sf::RenderTarget& target);
	};
}

