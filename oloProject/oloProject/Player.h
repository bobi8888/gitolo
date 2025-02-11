#pragma once
#include "Entity.h"

class Entity;

class Player :
    public Entity
{
private:
    //Variables
    bool isAttacking;

    //Initializer Methods
    void initVariables();

public:
    //Constructors/Destructors
    Player(sf::Texture& texture_sheet, float x, float y);

    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();

    MovementComponent* getMovementComponent();

    HitboxComponent* getHitboxComponent();

    //Methods
    void updateAttack();

    void loseHp(const int damage);

    void gainHp(const int heal);

    void gainExp(const int gainedExp);

    void updateAnimation(const float& deltaTime);

    void update(const float& deltaTime);

    void render(sf::RenderTarget& target);

    void updateLevel();
};

