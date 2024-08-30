#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Item.hpp"

class Weapon : public Item {
public:
    Weapon(const std::string &, double );
    Weapon* clone() const override;
    double getParam() const override;
    void print() const override;

private:
    double bonusDamage;
};

#endif