#include "Human.hpp"

Human::Human(double health = 50.0, double damage = 30.0, double mana = 20.0)
    : Character(health, damage, mana)
{
    addItemToInventory(new Weapon("Sword", 0.2));
    addItemToInventory(new Spell("Fireball", 0.2));
}

Human *Human::clone() const
{
    return new Human(*this);
}

void Human::type() const { std::cout << "Human: "; }