#pragma once
#include "Entity.h"

class Entity;

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
    void updateAttack();

    void updateAnimation(const float& deltaTime);

    void update(const float& deltaTime);

    void render(sf::RenderTarget& target);
};

