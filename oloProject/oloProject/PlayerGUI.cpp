#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf");
}

void PlayerGUI::initHPBar()
{
	
}

//Constructors & destructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();

	this->hpBar = new gui::Bar(player->getPosition());
}

PlayerGUI::~PlayerGUI()
{

}

//Methods
void PlayerGUI::update(const float deltaTime)
{
	this->hpBar->update(this->player->getMovementComponent()->getSpritePosition());
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}
