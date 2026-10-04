#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "Enemy.hpp"

class Enemy
{
public:
    explicit Enemy(int startingHealth)
        : health(startingHealth > 0 ? startingHealth : 0)
    {
    }

    void takeDamage(int amount)
    {
        if (amount <= 0)
        {
            return;
        }

        health = amount >= health ? 0 : health - amount;
    }

    int getHealth() const
    {
        return health;
    }

    bool isAlive() const
    {
        return health > 0;
    }

private:
    int health;
};

void addPoints(int& score, int points)
{
    score += points;
}

void printEnemies(const std::vector<Enemy>& enemies)
{
    for (std::size_t index = 0; index < enemies.size(); ++index)
    {
        std::cout
            << "Enemy " << index + 1
            << ": health = "
            << enemies[index].getHealth()
            << '\n';
    }
}

int main()
{
    constexpr int enemyCount = 3;
    constexpr int attackDamage = 25;
    constexpr int defeatPoints = 100;

    int score = 0;

    std::mt19937 randomEngine(12345u);
    std::uniform_int_distribution<int> healthDistribution(20, 50);

    std::vector<Enemy> enemies;

    for (int index = 0; index < enemyCount; ++index)
    {
        enemies.emplace_back(healthDistribution(randomEngine));
    }

    std::cout << "Starting enemies\n";
    printEnemies(enemies);

    int round = 1;

    while (!enemies.empty())
    {
        std::cout << "\nAttack round " << round << '\n';

        for (Enemy& enemy : enemies)
        {
            enemy.takeDamage(attackDamage);

            if (!enemy.isAlive())
            {
                addPoints(score, defeatPoints);
            }
        }

        enemies.erase(
            std::remove_if(
                enemies.begin(),
                enemies.end(),
                [](const Enemy& enemy)
                {
                    return !enemy.isAlive();
                }
            ),
            enemies.end()
        );

        printEnemies(enemies);

        std::cout
            << "Remaining enemies: " << enemies.size()
            << "\nScore: " << score
            << '\n';

        ++round;
    }

    std::cout
        << "\nAll enemies defeated!"
        << "\nFinal score: " << score
        << '\n';

    return 0;
}
