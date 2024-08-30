#include "Item.hpp"

Item::Item(const std::string &name) : name(name) {}

std::string Item::getName() const { return name; }