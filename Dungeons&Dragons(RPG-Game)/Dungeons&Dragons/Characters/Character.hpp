#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include "Inventory.hpp"
#include <cmath>

class Character
{
public:
    Character(double , double , double );

    double getHealth() const;
    double getDamage() const;
    double getMana() const;

    bool isAlive() const;

    virtual void takeDamage(double );

    void dealDamageViaAttack(Character &);
    
    void dealDamageViaSpell(Character &);

    void heal(double );

    void bleed(double );

    void printItems() const;

    void levelUp();
    
    void print() const;

    void addItemToInventory(Item *);

    void removeItem(Item *);

    virtual Character *clone() const = 0;

    virtual ~Character() = default;

    virtual void type() const;

    virtual void levelUpDragon();

    Inventory &getInventory();

protected:
    Inventory inventory;

private:
    double health;
    double damage;
    double mana;
};

#endif