#include "Armour.hpp"
Armour::Armour(const std::string &name, double bonusArmour)
    : Item(name), bonusArmour(bonusArmour) {}

Armour *Armour::clone() const
{
    return new Armour(*this);
}

double Armour::getParam() const
{
    return bonusArmour;
}

void Armour::print() const
{
    std::cout << "Armour: " << name << " - " << bonusArmour * 100 << "% bonus armour!\n";
}