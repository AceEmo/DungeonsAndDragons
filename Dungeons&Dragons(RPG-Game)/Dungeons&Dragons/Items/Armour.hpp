#ifndef ARMOUR_HPP
#define ARMOUR_HPP

#include "Item.hpp"

class Armour : public Item {
public:
    Armour(const std::string &, double );
    Armour* clone() const override;
    double getParam() const override;
    void print() const override;

private:
    double bonusArmour;
};

#endif