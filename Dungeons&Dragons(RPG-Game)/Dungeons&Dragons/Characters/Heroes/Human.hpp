#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Character.hpp"

class Human : public Character
{
public:
    Human(double , double , double );

    Human *clone() const override;

private:
    void type() const override;
};

#endif 