#include "Mage.hpp"

Mage::Mage(double health = 50.0, double damage = 10.0, double mana = 40.0)
    : Character(health, damage, mana)
{
    addItemToInventory(new Weapon("Sword", 0.2));
    addItemToInventory(new Spell("Fireball", 0.2));
}

Mage *Mage::clone() const
{
    return new Mage(*this);
}

void Mage::type() const
{
    std::cout << "Mage" << std::endl;
}