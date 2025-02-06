#pragma once
class AttributeComponent
{
public:
	//Leveling 
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePts;

	//Attributes
	unsigned health;
	unsigned strength;
	unsigned dexterity;
	unsigned charisma;
	unsigned intelligence;
	
	//Status
	//Health
	int hp;
	int hpMax;
	//Strength
	int damageMin;
	int damageMax;
	int endurance;
	//Dexterity
	int buildSpeed;
	int repairSpeed;
	int accuracy;
	int lockpick;
	//Charisma
	int barter;
	int convince;
	int conversation;
	int intimidation;
	//Intelligence
	int expMultiplier;
	int science;
	int hacking;
	//Other
	int luck;
	int totalSteps;

	//Constructors & Destroyer
	AttributeComponent(unsigned lvl);

	~AttributeComponent();

	//Methods
	void calculateExpNext();

	void updateStats();

	void levelUp();

	void update();
};

