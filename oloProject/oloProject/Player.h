#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:
    //Variables

    //Initializer Methods
    void initVariables();
    void initComponents();

public:
    //Constructors/Destructors
    Player();
    Player(sf::Texture& texture, float x, float y);
    virtual ~Player();

    //Methods
};

