#include "Spell.hpp"

Spell::Spell(const std::string &name, double bonusMana)
    : Item(name), bonusMana(bonusMana) {}

Spell *Spell::clone() const 
{
    return new Spell(*this);
}

double Spell::getParam() const
{
    return bonusMana;
}

void Spell::print() const 
{
    std::cout << "Spell: " << name << " - " << bonusMana * 100 << "% bonus spell damage!\n";
}
