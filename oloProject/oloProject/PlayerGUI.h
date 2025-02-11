#pragma once

#include "Player.h"
#include "GUI.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;

	gui::Bar* hpBar;

	void initFont();

	void initHPBar();

public:
	//Constructors & destructor
	PlayerGUI(Player* player);
	
	~PlayerGUI();

	//Methods
	void update(const float deltaTime);

	void render(sf::RenderTarget& target);
};

