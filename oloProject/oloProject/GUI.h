#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	//Methods
	const float convertToPixelsX(const float percent, const sf::VideoMode& videoMode);

	const float convertToPixelsY(const float percent, const sf::VideoMode& videoMode);

	const unsigned calculateCharSize(const sf::VideoMode& videoMode, const unsigned divisor = 60);

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
	//Bar===============================================================================
	class Bar
	{
	private:
		sf::Font font;
		sf::Text text;

		sf::RectangleShape barBack;
		sf::RectangleShape barFront;

		float maxWidth, height, xOffset, yOffset;

	public:
		//Constructors & Destructor
		Bar(
			const sf::VideoMode& video_Mode,
			const sf::Vector2f& position,
			const float width, const float height, 
			const float x_Offset, const float y_Offset,
			const std::string font
		);

		~Bar();

		//Methods
		void updatePosition(const sf::Vector2f position);

		void updateText(std::string string);

		void updateBarFrontSize(int value, int valueMax);

		void render(sf::RenderTarget& target);
	};

	//Sphere==============================================================
	class Sphere
	{
	private:
		sf::CircleShape circleBack;
		sf::CircleShape circleFront;

		float maxRadius, xOffset, yOffset;

	public:
		//Constructors & Destructor
		Sphere(
			const sf::VideoMode& video_Mode,
			const sf::Vector2f& position,
			const float radius, 
			const float x_Offset, const float y_Offset
		);

		//Sphere(sf::VideoMode& video_Mode, float radius, float x, float y);

		~Sphere();

		//Methods
		void updatePosition(const sf::Vector2f position);

		void updateCircleFrontSize(int value, int valueMax);

		void render(sf::RenderTarget& target);
	};

	//Dropdown List===============================================================================================

	class DropdownList
	{
		private:
			float keytime;
			float keytimeMax;

			sf::Font& font;

			Button* activeElement;

			std::vector<Button*> elementList;

			bool showList;

			//Put this somewhere that wont show up in other dropdown lists
			std::vector<std::string> valid_Resolutions = {
				"1920 x 1080",
				"1760 x 990",
				"1680 x 1050",
				//"1600 x 1200",
				"1660 x 900",
				//"1440 x 576",
				//"1440 x 480",
				"1366 x 786",
				"1280 x 1024",
				"1280 x 720",
				"1128 x 634",
				"1024 x 768",
				"800 x 600",
				"720 x 576",
				"720 x 480",
				"640 x 480"
			};

		public:
			//Constructors & Destructor
			//Settings: Resolution
			DropdownList(
				float xPos, float yPos,
				float width, float height,
				sf::Font& font, std::vector<std::string> list, unsigned char_size,
				int elementsNum, std::vector<std::string> counterList
			);

			//Basic Constructor
			DropdownList(
				float xPos, float yPos, 
				float width, float height, 
				sf::Font& font, std::vector<std::string> list, unsigned char_size,
				int elementsNum, unsigned default_index = 0
			);

			~DropdownList();

			//Accessors
			const unsigned short& getActiveElementId() const;

			const std::string& getActiveElementTextString() const;

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

