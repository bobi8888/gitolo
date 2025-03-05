#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf");
}

void PlayerGUI::initHpBar()
{
	this->hpBar = new gui::Bar(
		this->player->getSprite(),
		0.75f, 15.f, //widthRatio, barHeight
		-35.f, 2.f,  //x&y bar offset
		1.5f, -1.5f,  //x&y text offset
		"Fonts/RobotoCondensed-Regular.ttf"
	);
}

void PlayerGUI::initExpSphere()
{
	this->expSphere = new gui::Sphere(15.f, -50.f, -5.f);
}

//Constructors & destructor
PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& video_Mode)
	:videoMode(video_Mode)
{
	this->player = player;

	//guiAnchor = new sf::Vector2f(2,5
	//);

	this->initFont();

	this->initHpBar();

	this->initExpSphere();	
}

PlayerGUI::~PlayerGUI()
{
	std::cout << "Deleted PlayerGUI" << "\n";
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
