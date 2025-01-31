#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:
		short unsigned ButtonState;
		short unsigned ButtonId;

		sf::RectangleShape Rectangle;
		sf::Font* Font;
		sf::Text Text;
	
		sf::Color TextIdleColor;
		sf::Color TextHoverColor;
		sf::Color TextActiveColor;

		sf::Color IdleColor;
		sf::Color HoverColor;
		sf::Color ActiveColor;

		sf::Color OutlineIdleColor;
		sf::Color OutlineHoverColor;
		sf::Color OutlineActiveColor;

	public:	
		//Constructors & Destructor
		Button(
			float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle, sf::Color text_hover, sf::Color text_active,
			sf::Color idle, sf::Color hover, sf::Color active,
			sf::Color outlineIdle = sf::Color::Transparent, 
			sf::Color outlineHover = sf::Color::Transparent, 
			sf::Color outlineActive = sf::Color::Transparent,
			short unsigned buttonId = 0);

		virtual ~Button();

		//Accessors
		const bool isPressed() const;

		const std::string getText() const;

		const short unsigned& getId() const;

		//const short unsigned& getButtonState() const;

		//Modifiers
		void setText(const std::string text);

		void setId(const short unsigned id);

		//Methods
		void centerText();

		void update(const sf::Vector2i& mousePosWindow);

		void render(sf::RenderTarget& target);
	};

	//Dropdown List===============================================================================================

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
			DropdownList(
				float xPos, float yPos, 
				float width, float height, 
				sf::Font& font, std::string list[],
				int elementsNum, unsigned default_index = 0
			);

			~DropdownList();

			//Accessors
			const unsigned short& getActiveElementId() const;

			const bool getKeytime();

			//Methods
			void updateKeytime(const float& deltaTime);

			void update(const sf::Vector2i& mousePosWindow, const float& deltaTime);

			void render(sf::RenderTarget& target);
	};

	//Texture Selector===========================================================================================

	class TextureSelector
	{
		private:
			float gridSize;
			float keytime;
			const float keytimeMax;
			bool isActive;
			bool isHidden;
			sf::RectangleShape bounds;
			sf::Sprite sheet;
			sf::RectangleShape selector;
			sf::Vector2u mousePostionGrid;
			sf::IntRect textureRect;		
			Button* hide_button;

		public:
			//Constructors & Destructor
			TextureSelector(
				float x, float y, 
				float width, float height, 
				float gridSize,
				const sf::Texture* texture_sheet, 
				sf::Font& font, std::string text
			);

			~TextureSelector();

			//Accessors
			const bool& getIsActive() const;

			const sf::IntRect& getTextureRect() const;

			const bool getKeytime();

			//const short unsigned& getButtonState() const;

			//Methods
			void update(const sf::Vector2i& mousePositionWindow, const float& deltaTime);
			void updateKeytime(const float& deltaTime);

			void render(sf::RenderTarget& target);
	};
}

