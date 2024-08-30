#include "Dragon.hpp"
Dragon::Dragon(double health = 50.0, double damage = 25.0, double mana = 25.0)
    : Character(health, damage, mana), dragonArmourPercentage(0.15) {}

void Dragon::takeDamage(double points)
{
    Character::takeDamage(points * (1 - dragonArmourPercentage));
}

Dragon *Dragon::clone() const 
{
    return new Dragon(*this);
}

void Dragon::levelUpDragon()
{
    Character::levelUpDragon();
    dragonArmourPercentage += 0.05;
}

void Dragon::type() const
{
    std::cout << "Dragon: ";
}