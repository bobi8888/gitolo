#pragma once
class AttributeComponent
{
public:
	//Leveling 
	int level;
	unsigned exp;
	unsigned expNext;
	int attributePts;

	//Attributes
	int health;
	int strength;
	int dexterity;
	int charisma;
	int intelligence;
	
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

	void gainExp(const unsigned exp);

	void updateStats(const bool reset);

	void levelUpLuck();

	void updateLevel();

	void update();

	std::string debugPrint();
};

