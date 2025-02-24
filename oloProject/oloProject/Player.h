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
    Player(sf::Texture& texture_sheet, float xPosition, float yPosition);

    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();

    MovementComponent* getMovementComponent();

    HitboxComponent* getHitboxComponent();

    //Methods
    void updateAttack();

    void gainExp(const int gainedExp);

    void updateAnimation(const float& deltaTime);

    void update(const float& deltaTime);

    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool showHitbox = false);

    void updateLevel();
};
