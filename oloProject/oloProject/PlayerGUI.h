#pragma once

#include "Player.h"
#include "GUI.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::VideoMode& videoMode;
	sf::Font font;

	sf::Vector2f* guiAnchor;

	gui::Bar* hpBar;
	gui::Sphere* expSphere;

	void initFont();

	void initHpBar();

	void initExpSphere();

public:
	//Constructors & destructor
	PlayerGUI(Player* player, sf::VideoMode& video_Mode);
	
	~PlayerGUI();

	//Methods
	void update(const float deltaTime);

	void render(sf::RenderTarget& target);
};

