#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include "Character.hpp"

class Warrior : public Character
{
public:
    Warrior(double , double , double );

    Warrior *clone() const override;

private:
    void type() const override;
};

#endif