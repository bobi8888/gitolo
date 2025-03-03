#pragma once

class PauseMenu; 
class Player;
class PlayerGUI;
class TileMap;
class TransitionComponent;

class InteriorState
{
private:
	std::string name;

	sf::View view;
	sf::RenderTexture renderTexture;

	sf::Sprite renderSprite;

	sf::Shader mainShader;

	sf::Font font;
	sf::Text cursorText;

	//is this needed?
	PauseMenu* pauseMenu;

	Player* player;
	PlayerGUI* playerGUI;

	//Missing a texture here?
	TileMap* tileMap;
	const sf::IntRect texture_rect;

	TransitionComponent* transitionComponent;

public:
	//Constructors & Destructor
	InteriorState();
	
	~InteriorState();

};

