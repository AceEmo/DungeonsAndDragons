#ifndef DRAGON_HPP
#define DRAGON_HPP
#include "Character.hpp"

class Dragon : public Character
{
public:
    Dragon(double , double , double );

    void takeDamage(double ) final;

    Dragon *clone() const override;

    void levelUpDragon() override;

private:
    double dragonArmourPercentage;
    void type() const override;
};

#endif