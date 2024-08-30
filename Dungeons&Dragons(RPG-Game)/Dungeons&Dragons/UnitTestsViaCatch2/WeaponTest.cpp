#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Weapon.hpp"

TEST_CASE("Weapon class tests", "Weapon") {
    Weapon weapon("Sword of Doom", 0.5);

    SECTION("Clone creates a correct copy") {
        Weapon* cloned_weapon = weapon.clone();
        REQUIRE(cloned_weapon->getName() == "Sword of Doom");
        REQUIRE(cloned_weapon->getParam() == Approx(0.5));
        delete cloned_weapon;
    }

    SECTION("getParam returns correct bonus damage value") {
        REQUIRE(weapon.getParam() == Approx(0.5));
    }
}
