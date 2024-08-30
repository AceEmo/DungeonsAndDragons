#include "Character.hpp"

Character::Character(double health = 0.0, double damage = 0.0, double mana = 0.0)
    : health(health), damage(damage), mana(mana) {}

double Character::getHealth() const { return health; }
double Character::getDamage() const { return damage; }
double Character::getMana() const { return mana; }

bool Character::isAlive() const { return health > 0; }

void Character::takeDamage(double points)
{
    try
    {
        double totalDamage = points;
        for (const auto &item : inventory.getItems())
        {
            if (const Armour *armour = dynamic_cast<const Armour *>(item))
            {
                totalDamage *= (1 - armour->getParam());
            }
        }
        if (totalDamage <= 0)
            throw std::runtime_error("Negative damage value.");
        health -= totalDamage;
        if (health <= 0)
            health = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in taking damage: " << e.what() << std::endl;
    }
}

void Character::dealDamageViaAttack(Character &other)
{
    try
    {
        double totalDamage = damage;
        for (const auto &item : inventory.getItems())
        {
            if (const Weapon *weapon = dynamic_cast<const Weapon *>(item))
            {
                totalDamage *= (1 + weapon->getParam());
            }
        }
        if (totalDamage < 0)
            throw std::runtime_error("Negative damage value.");
        other.takeDamage(totalDamage);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in dealing damage via attack: " << e.what() << std::endl;
    }
}

void Character::dealDamageViaSpell(Character &other)
{
    try
    {
        double totalDamage = mana;
        for (const auto &item : inventory.getItems())
        {
            if (const Spell *spell = dynamic_cast<const Spell *>(item))
            {
                totalDamage *= (1 + spell->getParam());
            }
        }
        if (totalDamage < 0)
            throw std::runtime_error("Negative damage value.");
        other.takeDamage(totalDamage);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in dealing damage via Spell: " << e.what() << std::endl;
    }
}

void Character::heal(double points)
{
    try
    {
        if (points < 0)
            throw std::runtime_error("Negative healing value.");
        std::cout << "You got healed by " << round(points) << " points!\n";
        round(health += points);
        print();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in healing: " << e.what() << std::endl;
    }
}

void Character::bleed(double points)
{
    std::cout << "You are bleeding! You lost " << points << " points!\n";
    health -= points;
    print();
}

void Character::printItems() const
{
    inventory.printItems();
}

void Character::levelUp()
{
    double healthPoints = 0, damagePoints = 0, manaPoints = 0, totalPoints = 30;
    std::cout << "\n\033[32mLevel Up!\n";
    std::cout << "You have 30 points to allocate for health, damage, and mana.\n";
    std::cout << "You can allocate points in any way you like or choose to allocate them equally.\n";
    std::cout << "1. Allocate equally\n2. Allocate manually\nChoice: ";
    char choice;
    std::cin >> choice;
    if (choice == '1')
    {
        healthPoints += 10;
        damagePoints += 10;
        manaPoints += 10;
    }
    else
    {
        do
        {
            std::cout << "Enter points for health, damage, and mana (total must be = 30):\n";
            std::cout << "Health: ";
            std::cin >> healthPoints;
            std::cout << "Damage: ";
            std::cin >> damagePoints;
            std::cout << "Mana: ";
            std::cin >> manaPoints;
            if (healthPoints + damagePoints + manaPoints != totalPoints)
            {
                std::cout << "\nPlease allocate again.\n";
            }
        } while (healthPoints + damagePoints + manaPoints != totalPoints);
    }
    health += healthPoints;
    damage += damagePoints;
    mana += manaPoints;

    std::cout << "\nCongratulations! You have leveled up!\n";
    std::cout << "Current stats:\n\033[32m";
    print();
}

void Character::print() const
{
    std::cout << "\033[36m--------------\n";
    type();
    std::cout << "\nHealth: " << health << std::endl;
    std::cout << "Damage: " << damage << std::endl;
    std::cout << "Mana: " << mana << std::endl;
    std::cout << "--------------\033[36m\n";
}

void Character::addItemToInventory(Item *item)
{
    inventory.addItem(item);
}

void Character::removeItem(Item *item)
{
    inventory.removeItem(item);
}

void Character::type() const { std::cout << "Character: "; }

void Character::levelUpDragon()
{
    health += 10;
    damage += 10;
    mana += 10;
}

Inventory &Character::getInventory()
{
    return inventory;
}