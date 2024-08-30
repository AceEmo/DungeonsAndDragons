#ifndef MAGE_HPP
#define MAGE_HPP
#include "Character.hpp"

class Mage : public Character
{
public:
    Mage(double, double , double );

    Mage *clone() const override;

private:
    void type() const override;
};

#endif