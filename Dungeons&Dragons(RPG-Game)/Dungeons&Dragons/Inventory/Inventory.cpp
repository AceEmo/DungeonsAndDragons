#include "Inventory.hpp"
Inventory::Inventory() : items() {}

Inventory::Inventory(const Inventory &other) : items()
{
    for (const auto &item : other.items)
    {
        items.push_back(item->clone());
    }
}

Inventory &Inventory::operator=(const Inventory &other)
{
    Inventory copy(other);
    swap(copy);
    return *this;
}

void Inventory::swap(Inventory &other) noexcept
{
    using std::swap;
    swap(items, other.items);
}

Inventory::~Inventory()
{
    clearInvenotry();
}

void Inventory::removeItem(Item *item)
{
    auto it = std::find_if(items.begin(), items.end(), [&](Item *i)
                           { return i->getName() == item->getName(); });

    if (it != items.end())
    {
        delete *it;
        items.erase(it);
    }
}

void Inventory::addItem(Item *item)
{
    items.push_back(item->clone());
}

void Inventory::printItems() const
{
    std::cout << "\033[32mItems in inventory:\n";
    for (const auto &item : items)
    {
        item->print();
    }
    std::cout << "\033[0m";
    std::cout << std::endl;
}

const std::vector<Item *> &Inventory::getItems() const
{
    return items;
}

void Inventory::clearInvenotry()
{
    for (auto &item : items)
    {
        delete item;
    }
    items.clear();
}