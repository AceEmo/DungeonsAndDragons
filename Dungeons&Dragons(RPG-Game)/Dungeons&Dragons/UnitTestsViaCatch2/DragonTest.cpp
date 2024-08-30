#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Dragon.hpp"

TEST_CASE("Dragon class tests", "Dragon") {
    Dragon dragon(50, 25, 25);

    SECTION("Initial values are set correctly") {
        REQUIRE(dragon.getHealth() == 50);
        REQUIRE(dragon.getDamage() == 25);
        REQUIRE(dragon.getMana() == 25);
    }

    SECTION("Clone creates a correct copy") {
        Dragon *copy = dragon.clone();
        REQUIRE(copy->getHealth() == dragon.getHealth());
        REQUIRE(copy->getDamage() == dragon.getDamage());
        REQUIRE(copy->getMana() == dragon.getMana());
        delete copy;
    }

    SECTION("Take damage reduces health correctly considering armour") {
        dragon.takeDamage(10);
        REQUIRE(dragon.getHealth() == 43);
    }
}
