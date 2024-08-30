#include "Play.hpp"
Play::Play(const std::string &mazeFile)
{
    std::cout << "\033[1;36m"; 
    std::cout << "*****************************************\n";
    std::cout << "*  \033[1;35mDungeons and Dragons\033[1;36m!  *\n";
    std::cout << "          *   \033[1;35mLet the adventure begin\033[1;36m!   *\n";
    std::cout << "*****************************************\n";
    std::cout << "\033[0m";
    
    maze.chooseCharacter();
    gamePlay(mazeFile);
}

void Play::gamePlay(const std::string &mazeFile)
{   
    try
    {
        std::ifstream file(mazeFile);
        if (!file.is_open())
        {
            throw std::runtime_error("Maze file not found.");
        }
        while (true)
        {
            maze.loadMaze(file);
            maze.placeMonstersAndTreasures(maze.getMonsters(), maze.getTreasures());
            if (maze.findPath(0, 0, maze.getM() - 1, maze.getN() - 1))
            {
                maze.levels();
            }
            if (file.eof())
            {
                file.close();
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in gamePlay: " << e.what() << std::endl;
    }
}