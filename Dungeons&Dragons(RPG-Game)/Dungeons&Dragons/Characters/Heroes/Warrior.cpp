#include "Warrior.hpp"
Warrior::Warrior(double health = 50.0, double damage = 40.0, double mana = 10.0)
    : Character(health, damage, mana)
{
    addItemToInventory(new Weapon("Sword", 0.2));
    addItemToInventory(new Spell("Fireball", 0.2));
}

Warrior *Warrior::clone() const
{
    return new Warrior(*this);
}

void Warrior::type() const
{
    std::cout << "Warrior" << std::endl;
}