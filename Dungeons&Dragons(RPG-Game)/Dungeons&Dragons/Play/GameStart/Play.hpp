#ifndef PLAY_HPP
#define PLAY_HPP

#include "Maze.hpp"    

class Play
{
public:
    Play(const std::string &);

    void gamePlay(const std::string &);

private:
    Maze maze;
};

#endif