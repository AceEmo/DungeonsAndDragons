#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

class Item {
public:
    Item(const std::string &);
    std::string getName() const;
    virtual ~Item() = default;
    virtual double getParam() const = 0;
    virtual Item* clone() const = 0;
    virtual void print() const = 0;

protected:
    std::string name;
};

#endif
