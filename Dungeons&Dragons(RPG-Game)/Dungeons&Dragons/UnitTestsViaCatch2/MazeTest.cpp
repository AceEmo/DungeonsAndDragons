#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Maze.hpp"

TEST_CASE("Maze class tests", "Maze")
{
    SECTION("Load maze from file")
    {
        Maze maze;
        std::ifstream file("mazeTest.txt");
        maze.loadMaze(file);
        REQUIRE(maze.getN() == 5);
        REQUIRE(maze.getM() == 5);
        REQUIRE(maze.getMonsters() == 1);
        REQUIRE(maze.getTreasures() == 1);
    }

    SECTION("Choose character")
    {
        Maze maze;
        maze.chooseCharacter();
        REQUIRE(maze.getPlayer() != nullptr);
    }

    SECTION("Place monsters and treasures")
    {
        Maze maze;
        std::ifstream file("mazeTest.txt");
        maze.loadMaze(file);
        maze.placeMonstersAndTreasures(1, 1);
        REQUIRE(maze.getMonsters() == 1);
        REQUIRE(maze.getTreasures() == 1);
    }

    SECTION("Find path in maze")
    {
        Maze maze;
        std::ifstream file("mazeTest.txt");
        maze.loadMaze(file);
        maze.chooseCharacter();
        bool pathFound = maze.findPath(0, 0, maze.getM() - 1, maze.getN() - 1);
        REQUIRE(pathFound == true);
        std::cout << "\nPath found\n";
    }

    SECTION("Add and remove item to/from player's inventory")
    {
        Maze maze;
        maze.chooseCharacter();
        Character* player = maze.getPlayer();
        int newInventorySize = player->getInventory().getItems().size();

        Item *newItem = new Armour("Armour", 0.2);

        player->addItemToInventory(newItem);

        int finalInventorySize = player->getInventory().getItems().size();
        REQUIRE(finalInventorySize == newInventorySize + 1);
        player->printItems();

        player->removeItem(newItem);
        REQUIRE(player->getInventory().getItems().size() == newInventorySize);

        delete newItem;
    }

    SECTION("Heal level up")
    {
        Maze maze;
        maze.chooseCharacter();
        double healthBeforeHeal = maze.getPlayer()->getHealth();
        maze.healLevelUp();
        double healthAfterHeal = maze.getPlayer()->getHealth();
        REQUIRE(healthAfterHeal > healthBeforeHeal);
        std::cout << "Player healed\n";
    }
}
