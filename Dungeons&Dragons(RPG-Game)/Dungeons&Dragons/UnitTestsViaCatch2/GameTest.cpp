#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Game.hpp"
#include "Dragon.hpp"
#include "Human.hpp"

TEST_CASE("Game class tests", "Game") {
    SECTION("Add and remove characters from game") {
        Game game;
        Human *hero1 = new Human(100, 20, 50);
        Human *hero2 = new Human(120, 25, 60);
        Dragon *dragon1 = new Dragon(200, 30, 100);

        game.add(hero1);
        game.add(hero2);
        game.add(dragon1);

        REQUIRE(game.getCharacters().size() == 3);

        game.remove(hero1);
        REQUIRE(game.getCharacters().size() == 2);

        game.remove(hero2);
        REQUIRE(game.getCharacters().size() == 1);

        game.remove(dragon1);
        REQUIRE(game.getCharacters().size() == 0);

        delete hero1;
        delete hero2;
        delete dragon1;
    }

    SECTION("Battle between characters ends with Hero winning") {
        Game game;
        Human *hero = new Human(10, 10, 10);
        Dragon *dragon = new Dragon(1, 1, 1);

        game.add(hero);
        game.add(dragon);

        REQUIRE(game.battle(hero, dragon) == true);

        delete hero;
        delete dragon;
    }

    SECTION("Battle between characters ends correctly with Dragon winning") {
        Game game;
        Human *hero = new Human(1, 1, 1);
        Dragon *dragon = new Dragon(10, 10, 10);

        game.add(hero);
        game.add(dragon);

        REQUIRE(game.battle(hero, dragon) == false);
        REQUIRE(game.getCharacters().empty());

        delete hero;
        delete dragon;
    }

    SECTION("Next level increases level for all characters except dragons") {
        Game game;
        Human *hero1 = new Human(100, 20, 50);
        Dragon *dragon = new Dragon(200, 30, 100);

        game.add(hero1);
        game.add(dragon);

        game.nextLevel();
        for (Character *character : game.getCharacters()) {
            if (!dynamic_cast<Dragon*>(character)) {
                REQUIRE(character->getHealth() > 100);
                REQUIRE(character->getDamage() > 20);
                REQUIRE(character->getMana() > 50);
            }
        }

        delete hero1;
        delete dragon;
    }
}
