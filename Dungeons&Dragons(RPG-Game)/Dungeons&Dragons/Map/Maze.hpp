#ifndef MAZE_HPP
#define MAZE_HPP

#include "Game.hpp"
#include "Inventory.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

class Maze
{
public:
    Maze();

    void loadMaze(std::ifstream &);

    void chooseCharacter();

    void placeMonstersAndTreasures(int , int );

    bool findPath(int , int , int , int );

    void levels();

    void printMaze() const;

    Character *getPlayer() const;

    int getN() const;

    int getM() const;

    void clearMaze();

    int getMonsters() const;

    int getTreasures() const;

    void healLevelUp();

private:
    std::vector<std::vector<char>> maze;
    Game game;
    Inventory inventory;
    int N = 0;
    int M = 0;
    int level = 1;
    int monsters = 0;
    int treasures = 0;

    bool canStep(int , int ) const;

    bool isItemAdable(Character *, Item *);

    int randomIndex() const;

    void placeRandomly(char );

    void dragonLevelUp(Dragon *);
};

#endif