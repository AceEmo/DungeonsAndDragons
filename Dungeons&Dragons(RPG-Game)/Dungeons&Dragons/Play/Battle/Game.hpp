#ifndef GAME_HPP
#define GAME_HPP

#include "Character.hpp"
#include "Dragon.hpp"
#include "Human.hpp"
#include "Mage.hpp"
#include "Warrior.hpp"
#include <ctime>

class Game
{
public:
    Game();

    Game(const Game &);

    Game &operator=(const Game &);

    void swap(Game &);

    ~Game();

    void nextLevel();

    void add(Character *);

    void remove(Character *);

    void print() const;

    bool battle(Character *, Character *);

    const std::vector<Character *> &getCharacters() const;

private:
    std::vector<Character *> characters;

    bool random() const;

    void DragonBattle(Character *, Character *);

    void HeroBattle(Character *, Character *);

    bool isDragon(Character *) const;

    void heroWon(Character *, Character *, double );

    void dragonWon(Character *, Character *);

    void gameOver();

    void printCurrentStats(Character *, Character *) const;
};

#endif 