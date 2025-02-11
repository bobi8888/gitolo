#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf");
}

//void PlayerGUI::initHPBar()
//{
//	
//}

//Constructors & destructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();

	this->hpBar = new gui::Bar(20.f, 5.f, this->player->getSpritePosition());
}

PlayerGUI::~PlayerGUI()
{

}

//Methods
void PlayerGUI::update(const float deltaTime)
{
	this->hpBar->updateBarFrontSize(
		this->player->getAttributeComponent()->hp, 
		this->player->getAttributeComponent()->hpMax
	);

	this->hpBar->updatePosition(
		sf::Vector2f(
			std::floor(this->player->getSpritePosition().x + this->player->getSpriteGlobalBounds().width / 2.f),
			std::floorf(this->player->getSpritePosition().y + this->player->getSpriteGlobalBounds().height)
		)
	);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}
