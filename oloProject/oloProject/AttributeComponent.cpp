#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned lvl)
{
	this->level = lvl;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(lvl, 3) - 6 * pow(lvl, 2) + (lvl * 17) - 12));
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

	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::calculateExpNext()
{

}

void AttributeComponent::gainExp(const unsigned exp)
{
	this->exp += exp;

	this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
	//Health
	this->hpMax = this-> health * 9 + this->health;
	//Strength
	this->damageMin = this->strength * 2 + this->strength / 4;
	this->damageMax = this->strength * 2 + this->strength / 2;
	this->endurance = this->strength * 2 + this->strength;
	//Dexterity
	this->buildSpeed = this->dexterity * 2 + this->dexterity;
	this->repairSpeed = this->dexterity * 2 + this->dexterity;
	this->accuracy = this->dexterity * 2 + this->dexterity;
	this->lockpick = this->dexterity * 2 + this->dexterity;
	//Charisma
	this->barter = this->charisma * 2 + this->charisma;
	this->convince = this->charisma * 2 + this->charisma;
	this->conversation = this->charisma * 2 + this->charisma;
	this->intimidation = this->charisma * 2 + this->charisma;
	//Intelligence
	this->expMultiplier = this->intelligence * 2 + this->intelligence;
	this->science = this->intelligence * 2 + this->intelligence;
	this->hacking = this->intelligence * 2 + this->intelligence;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::levelUpLuck()
{
	++this->luck;
}

void AttributeComponent::updateLevel()
{
	while (this->exp > this->expNext)
	{
		++this->level;

		this->exp -= this->expNext;

		this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level, 3)	- 6 * pow(this->level, 2) + (this->level * 17) - 12));

		++this->attributePts;	
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}

std::string AttributeComponent::debugPrint()
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
	<< "Exp: " << this->exp << "\n"
	<< "NextExp: " << this->expNext << "\n"
	<< "Attribute points: "  << this->attributePts << "\n";

	return ss.str();
}
