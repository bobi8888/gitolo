#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf");
}

void PlayerGUI::initHpBar()
{
	this->hpBar = new gui::Bar(
		20.f, 5.f,
		this->player->getSpritePosition(),
		"Fonts/RobotoCondensed-Regular.ttf"
	);
}

void PlayerGUI::initExpSphere()
{
	this->expSphere = new gui::Sphere(
		10.f, this->player->getSpritePosition()
	);
}

//Constructors & destructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();

	this->initHpBar();

	this->initExpSphere();
	
}

PlayerGUI::~PlayerGUI()
{

}

//Methods
void PlayerGUI::update(const float deltaTime)
{
	//HP Bar
	this->hpBar->updateBarFrontSize(
		this->player->getAttributeComponent()->hp, 
		this->player->getAttributeComponent()->hpMax
	); 

	//to_string is an expensive opperation
	this->hpBar->updateText(
		std::to_string(this->player->getAttributeComponent()->hp) 
		+ " :|: " 
		+ std::to_string(this->player->getAttributeComponent()->hpMax)
	);

	this->hpBar->updatePosition(
		sf::Vector2f(
			std::floor(this->player->getSpritePosition().x + this->player->getSpriteGlobalBounds().width / 2.f),
			std::floor(this->player->getSpritePosition().y + this->player->getSpriteGlobalBounds().height)
		)
	);

	//EXP SPHERE
	this->expSphere->updateCircleFrontSize(
		this->player->getAttributeComponent()->exp + 1,
		this->player->getAttributeComponent()->expNext
	);

	this->expSphere->updatePosition(
		sf::Vector2f(
			std::floor(this->player->getSpritePosition().x + this->player->getSpriteGlobalBounds().width / 3.f),
			std::floor(this->player->getSpritePosition().y + this->player->getSpriteGlobalBounds().height)
		)
	);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->hpBar->render(target);

	this->expSphere->render(target);
}
