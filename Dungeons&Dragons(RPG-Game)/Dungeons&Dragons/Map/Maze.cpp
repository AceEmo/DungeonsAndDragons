#include "Maze.hpp"
Maze::Maze() : maze() {}

void Maze::loadMaze(std::ifstream &file)
{
    clearMaze();
    try
    {
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (line.empty())
                    break;
                std::vector<char> row;
                std::string itemType;
                std::string itemName;
                double param;
                if (monsters != 0 && treasures != 0)
                {
                    std::istringstream iss(line);
                    iss >> itemType >> itemName >> param;
                    if (itemType == "Weapon")
                    {
                        inventory.addItem(new Weapon(itemName, param / 100));
                    }
                    else if (itemType == "Armour")
                    {
                        inventory.addItem(new Armour(itemName, param / 100));
                    }
                    else if (itemType == "Spell")
                    {
                        inventory.addItem(new Spell(itemName, param / 100));
                    }
                }
                bool flag = true;
                for (char c : line)
                {
                    if (c == '.' || c == '#')
                    {
                        row.push_back(c);
                    }
                    else if (c >= '0' && c <= '9')
                    {
                        if (monsters == 0 && flag)
                        {
                            monsters = c - '0';
                            flag = false;
                        }
                        else if (treasures == 0 && monsters != 0 && !flag)
                        {
                            treasures = c - '0';
                        }
                    }
                }
                if (!row.empty())
                {
                    maze.push_back(row);
                }
            }
            N = maze.size();
            if (N > 0)
                M = maze[0].size();

            if (N == 0 || M == 0)
                throw std::runtime_error("Invalid maze dimensions.");

            if (monsters == 0 || treasures == 0)
                throw std::runtime_error("Invalid number of monsters or treasures.");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error while loading maze: " << e.what() << std::endl;
    }
}

void Maze::chooseCharacter()
{
    int choice;
    std::cout << "\033[31mChoose your character:\n1. Human\n2. Mage\n3. Warrior\nChoice: ";
    std::cin >> choice;

    try
    {
        Character *player;
        switch (choice)
        {
        case 1:
        {
            player = new Human(50, 30, 20);
            if (player == nullptr)
                throw std::runtime_error("Memory allocation failed.");
            break;
        }
        case 2:
        {
            player = new Mage(50, 10, 40);
            if (player == nullptr)
                throw std::runtime_error("Memory allocation failed.");
            break;
        }
        case 3:
        {
            player = new Warrior(50, 40, 10);
            if (player == nullptr)
                throw std::runtime_error("Memory allocation failed.");
            break;
        }
        case 777:
        {
            player = new Human(5000, 1000, 1000);
            std::cout << "Welcome Admin!\n";
            if (player == nullptr)
                throw std::runtime_error("Memory allocation failed.");
            break;
        }
        default:
        {
            player = new Human(50, 30, 20);
            if (player == nullptr)
                throw std::runtime_error("Memory allocation failed.");
            break;
        }
        }
        game.add(player);
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Error in choosing character: \n";
        return;
    }

    std::cout << "\033[0m";
}

void Maze::placeMonstersAndTreasures(int monsters, int treasures)
{
    for (int i = 0; i < monsters; ++i)
    {
        placeRandomly('M');
    }
    for (int i = 0; i < treasures; ++i)
    {
        placeRandomly('T');
    }
    for (int i = 0; i < (monsters + treasures) / 3; ++i)
    {
        placeRandomly('H');
    }
    printMaze();
}
bool Maze::findPath(int sx, int sy, int gx, int gy)
{
    Character *player = getPlayer();
    if (player == nullptr)
        return false;

    if (sx == gx && sy == gy)
    {
        maze[sy][sx] = '+';
        return true;
    }

    if (!canStep(sx, sy))
    {
        return false;
    }

    if (maze[sy][sx] == 'T')
    {
        printMaze();
        std::cout << "\033[34mYou found a new item!\033[0m\n";
        Item *item = inventory.getItems()[randomIndex()];
        if (!isItemAdable(player, item))
        {
            player->addItemToInventory(item);
            inventory.removeItem(item);
        }
        player->printItems();
    }

    if (maze[sy][sx] == 'M')
    {
        Dragon *dragon = new Dragon(50, 25, 25);
        dragonLevelUp(dragon);
        printMaze();
        if (!game.battle(player, dragon))
        {
            return false;
        }
        std::cout << "Monster killed at (" << sx << "," << sy << ")!\n";
    }

    if (maze[sy][sx] == 'H')
    {
        printMaze();
        std::cout << "\033[33mYou found a healing potion!\n";
        healLevelUp();
        std::cout << "\033[0m";
    }

    maze[sy][sx] = '+';

    if (findPath(sx + 1, sy, gx, gy) || // right
        findPath(sx, sy + 1, gx, gy) || // down
        findPath(sx - 1, sy, gx, gy) || // left
        findPath(sx, sy - 1, gx, gy))   // up
    {
        return true;
    }

    maze[sy][sx] = '.';
    return false;
}

void Maze::levels()
{
    printMaze();
    game.nextLevel();
    level++;
}

void Maze::printMaze() const
{
    if (getPlayer() == nullptr)
    {
        return;
    }
    std::cout << "\n";
    for (int i = 0; i < M; ++i)
    {
        std::cout << "\033[1;33m" << std::setw(3) << '-' << "\033[1;0m";
    }
    std::cout << "\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (maze[i][j] == '+')
            {
                std::cout << "\033[1;31m" << std::setw(3) << maze[i][j] << "\033[1;0m";
            }
            else if (maze[i][j] == 'M')
            {
                std::cout << "\033[1;32m" << std::setw(3) << maze[i][j] << "\033[1;0m";
            }
            else if (maze[i][j] == 'T'){
                std::cout << "\033[1;35m" << std::setw(3) << maze[i][j] << "\033[1;0m";
            }
            else if (maze[i][j] == 'H')
            {
                std::cout << "\033[1;33m" << std::setw(3) << maze[i][j] << "\033[1;0m";
            }
            else
            {
                std::cout << "\033[34m" << std::setw(3) << maze[i][j] << "\033[0m";
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < M; ++i)
    {
        std::cout << "\033[1;33m" << std::setw(3) << '-' << "\033[1;0m";
    }
    std::cout << "\n\n";
}

Character *Maze::getPlayer() const
{
    for (const auto &character : game.getCharacters())
    {
        if (!dynamic_cast<Dragon *>(character))
        {
            return character;
        }
    }
    return nullptr;
}

int Maze::getN() const
{
    return N;
}

int Maze::getM() const
{
    return M;
}

void Maze::clearMaze()
{
    maze.clear();
    monsters = 0;
    treasures = 0;
    inventory.clearInvenotry();
}

int Maze::getMonsters() const
{
    return monsters;
}

int Maze::getTreasures() const
{
    return treasures;
}

bool Maze::canStep(int x, int y) const
{
    return x >= 0 && x < M && y >= 0 && y < N && maze[y][x] != '#' && maze[y][x] != '+';
}

bool Maze::isItemAdable(Character *player, Item *item)
{
    for (const auto &it : player->getInventory().getItems())
    {
        if (dynamic_cast<Weapon *>(it) && dynamic_cast<Weapon *>(item) || dynamic_cast<Spell *>(it) && dynamic_cast<Spell *>(item) || dynamic_cast<Armour *>(it) && dynamic_cast<Armour *>(item))
        {
            player->printItems();
            std::cout << "\033[32mNew item: \n";
            item->print();

            std::cout << "\nYou already have an item of this type!\nDo you want to exchange it for the new one?\n1. Yes\n2. No\nChoice: ";
            char choice;
            std::cin >> choice;
            if (choice == '1')
            {
                player->removeItem(it);
                player->addItemToInventory(item);
            }
            inventory.removeItem(item);
            return true;
            std::cout << "\033[0m";
        }
    }
    return false;
}

int Maze::randomIndex() const
{
    srand(time(0));
    return rand() % inventory.getItems().size();
}

void Maze::placeRandomly(char item)
{
    int x, y;
    srand(time(0));
    do
    {
        x = rand() % M;
        y = rand() % N;
    } while (maze[y][x] != '.');
    maze[y][x] = item;
}

void Maze::dragonLevelUp(Dragon *dragon)
{
    for (int i = 1; i < level; ++i)
    {
        dragon->levelUpDragon();
    }
}

void Maze::healLevelUp()
{
    double totalHealPoints = 0.05;
    for (int i = 1; i < level; ++i)
    {
        totalHealPoints += 0.05;
    }
    getPlayer()->heal(totalHealPoints * getPlayer()->getHealth());
}