#include "Weapon.hpp"

Weapon::Weapon(const std::string &name, double bonusDamage)
    : Item(name), bonusDamage(bonusDamage) {}

Weapon *Weapon::clone() const
{
    return new Weapon(*this);
}

double Weapon::getParam() const
{
    return bonusDamage;
}

void Weapon::print() const 
{
    std::cout << "Weapon: " << name << " - " << bonusDamage * 100 << "% bonus attack damage!\n";
}