#include "Enemy.hpp"

Enemy::Enemy(int startingHealth)
    : health(startingHealth > 0 ? startingHealth : 0)
{}

void Enemy::takeDamage(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    health = amount >= health ? 0 : health - amount;
}

int Enemy::getHealth() const
{
    return health;
}

bool Enemy::isAlive() const
{
    return health > 0;
}
Enemy::identifies a function as belonging to the class.
