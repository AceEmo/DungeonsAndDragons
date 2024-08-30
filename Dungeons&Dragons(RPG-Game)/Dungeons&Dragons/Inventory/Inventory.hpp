#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Item.hpp"
#include "Armour.hpp"
#include "Spell.hpp"
#include "Weapon.hpp"
#include <vector>
#include <algorithm>

class Inventory
{
public:
    Inventory();

    Inventory(const Inventory &);

    Inventory &operator=(const Inventory &);

    void swap(Inventory &) noexcept;

    ~Inventory();

    void removeItem(Item *);

    void addItem(Item *);

    void printItems() const;

    const std::vector<Item *> &getItems() const;

    void clearInvenotry();

private:
    std::vector<Item *> items;
};

#endif 
