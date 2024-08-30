#ifndef SPELL_HPP
#define SPELL_HPP
#include "Item.hpp"

class Spell : public Item {
public:
    Spell(const std::string &, double );
    Spell* clone() const override;
    double getParam() const override;
    void print() const override;

private:
    double bonusMana;
};

#endif 