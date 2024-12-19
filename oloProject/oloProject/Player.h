#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:
    //Variables
    bool IsAttacking;
    //Initializer Methods
    void initVariables();

public:
    //Constructors/Destructors
    Player();
    Player(sf::Texture& texture_sheet, float x, float y);
    virtual ~Player();

    //Methods
    virtual void update(const float& deltaTime);
};

