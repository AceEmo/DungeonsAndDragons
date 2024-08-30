#include "Game.hpp"
Game::Game() : characters() {}

Game::Game(const Game &other)
{
    characters.reserve(other.characters.size());
    for (Character *character : other.characters)
    {
        characters.push_back(character->clone());
    }
}

Game &Game::operator=(const Game &other)
{
    Game copy(other);
    swap(copy);
    return *this;
}

void Game::swap(Game &other)
{
    using std::swap;
    swap(characters, other.characters);
}

Game::~Game()
{
    for (Character *character : characters)
    {
        delete character;
    }
}

void Game::nextLevel()
{
    for (Character *character : characters)
    {
        if (!dynamic_cast<Dragon *>(character))
            character->levelUp();
    }
}

void Game::add(Character *character)
{
    characters.push_back(character->clone());
}

void Game::print() const
{
    for (const Character *character : characters)
    {
        character->print();
    }
}

bool Game::battle(Character *character1, Character *character2)
{
    double healthBeforeBattle;
    if (random())
    {
        std::swap(character1, character2);
    }

    if (!isDragon(character1))
        healthBeforeBattle = character1->getHealth();
    else
        healthBeforeBattle = character2->getHealth();

    std::cout << "\033[91mBattle begins!\n\033[0m";
    printCurrentStats(character1, character2);
    while (character1->isAlive() && character2->isAlive())
    {
        if (!isDragon(character1))
            HeroBattle(character1, character2);
        else
            DragonBattle(character1, character2);

        if (!character2->isAlive())
            break;
        printCurrentStats(character1, character2);
        if (isDragon(character2))
            DragonBattle(character2, character1);
        else
            HeroBattle(character2, character1);

        if (character1->isAlive())
            printCurrentStats(character1, character2);
    }

    if ((character1->isAlive() && !isDragon(character1)) || (character2->isAlive() && !isDragon(character2)))
    {
        heroWon(character1, character2, healthBeforeBattle);
        return true;
    }
    else
    {
        dragonWon(character1, character2);
        gameOver();
        return false;
    }
}

const std::vector<Character *> &Game::getCharacters() const
{
    return characters;
}

void Game::remove(Character *character)
{
    auto it = std::find_if(characters.begin(), characters.end(), [&](Character *i)
                           { return i->getHealth() == character->getHealth(); });
    if (it != characters.end())
    {
        delete *it;
        characters.erase(it);
    }
}

bool Game::random() const
{
    srand(time(0));
    return rand() % 2;
}

void Game::DragonBattle(Character *character1, Character *character2)
{
    std::cout << "\033[91mDragon attacks!\n\033[0m";
    if (random())
        character1->dealDamageViaAttack(*character2);
    else
        character1->dealDamageViaSpell(*character2);
}

void Game::HeroBattle(Character *character1, Character *character2)
{
    std::cout << "\033[95mHero's turn!\n";
    char choice;
    std::cout << "Choose attack type for ";
    character1->type();
    std::cout << "\n1. Physical Attack\n2. Spell Attack\n"
              << "Choice: ";
    std::cin >> choice;
    if (choice == '1')
    {
        character1->dealDamageViaAttack(*character2);
    }
    else if (choice == '2')
    {
        character1->dealDamageViaSpell(*character2);
    }
    else
    {
        std::cout << "Invalid choice. Defaulting to Physical Attack.\n";
        character1->dealDamageViaAttack(*character2);
    }
    std::cout << "\033[0m";
}

bool Game::isDragon(Character *character) const
{
    return dynamic_cast<Dragon *>(character);
}

void Game::heroWon(Character *character1, Character *character2, double healthBeforeBattle)
{
    std::cout << "\033[91m";
    if (!isDragon(character1))
    {
        character1->type();
        std::cout << "wins!\n";
        character2->type();
        std::cout << "was eliminated!\n";
        if (character1->getHealth() < 0.5 * healthBeforeBattle)
            character1->heal(0.5 * healthBeforeBattle);
        else
            character1->bleed(0.05 * healthBeforeBattle);
        remove(character2);
    }
    else
    {
        character2->type();
        std::cout << "wins!\n";
        character1->type();
        std::cout << "was eliminated!\n";
        if (character2->getHealth() < 0.5 * healthBeforeBattle)
            character2->heal(0.5 * healthBeforeBattle);
        else
            character2->bleed(0.05 * healthBeforeBattle);
        remove(character1);
    }
    std::cout << "\033[91m";
}

void Game::dragonWon(Character *character1, Character *character2)
{
    std::cout << "\033[91m";
    if (isDragon(character1))
    {
        character1->type();
        std::cout << "wins!\n";
        character2->type();
        std::cout << "was eliminated!\n";
        remove(character2);
    }
    else
    {
        character2->type();
        std::cout << "wins!\n";
        character1->type();
        std::cout << "was eliminated!\n";
        remove(character1);
    }
    std::cout << "\033[0m";
}

void Game::gameOver()
{
    std::cout << "\033[41mGame Over!\033[0m\n";
    for (Character *character : characters)
    {
        delete character;
    }
    characters.clear();
}

void Game::printCurrentStats(Character *character1, Character *character2) const
{
    character1->print();
    character2->print();
}