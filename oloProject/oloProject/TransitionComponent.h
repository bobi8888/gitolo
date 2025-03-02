#pragma once

class TransitionComponent
{
private:
	class TransitionZone
	{
	public:
		sf::RectangleShape hitbox;

		bool isActive;

		TransitionZone(
			float xPos, float yPos,
			float width, float height
			): isActive(true) 
		{
			this->hitbox.setSize(sf::Vector2f(width, height));

			this->hitbox.setOrigin(
				sf::Vector2f(
					width / 2.f,
					height / 2.f
				)
			);

			this->hitbox.setPosition(xPos, yPos);

			this->hitbox.setFillColor(sf::Color(255, 125, 0, 150));
		}
	};

	std::map <std::string, TransitionZone*> transitions;

public:
	//Constructors & Destructor
	TransitionComponent();
	
	~TransitionComponent();

	//Methods
	void render(sf::RenderTarget& target);
	void addTransitionZone(
		const std::string key,
		float xPos, float yPos,
		float width, float height
	);
};

