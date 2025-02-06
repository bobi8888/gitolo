#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned lvl)
{
	this->level = lvl;
	this->exp = 0;
	this->expNext = 
		static_cast<int>(
			(50 / 3) 
			* (
				pow(lvl, 3)
				- 6 * pow(lvl, 2)
				+ (lvl * 17) 
				)
		)
	;

	std::cout << expNext;

	this->attributePts = 2;

	this->health = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->charisma = 1;
	this->intelligence = 1;

	//Health
	this->hp = 10;
	this->hpMax = 10;
	//Strength
	this->damageMin = 0;
	this->damageMax = 3;
	this->endurance = 10;
	//Dexterity
	this->buildSpeed = 0;
	this->repairSpeed = 0;
	this->accuracy = 0;
	this->lockpick = 0;
	//Charisma
	this->barter = 0;
	this->convince = 0;
	this->conversation = 0;
	this->intimidation = 0;
	//Intelligence
	this->expMultiplier = 1;
	this->science = 0;
	this->hacking = 0;
	//Other
	this->luck = 1;
	this->totalSteps = 0;
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::calculateExpNext()
{

}

void AttributeComponent::updateStats()
{

}

void AttributeComponent::levelUp()
{

}

void AttributeComponent::update()
{

}
