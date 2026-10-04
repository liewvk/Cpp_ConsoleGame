#pragma once

class Enemy
{
public:
    explicit Enemy(int startingHealth);

    void takeDamage(int amount);

    int getHealth() const;
    bool isAlive() const;

private:
    int health;
};

