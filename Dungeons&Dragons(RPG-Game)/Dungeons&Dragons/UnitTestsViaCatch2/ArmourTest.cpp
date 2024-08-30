#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Armour.hpp"

TEST_CASE("Armour class tests", "Armour") {
    Armour armour("Steel Armour", 0.25);

    SECTION("Clone creates a correct copy") {
        Armour* cloned_armour = armour.clone();
        REQUIRE(cloned_armour->getName() == "Steel Armour");
        REQUIRE(cloned_armour->getParam() == Approx(0.25));
        delete cloned_armour;
    }

    SECTION("getParam returns correct bonus armour value") {
        REQUIRE(armour.getParam() == Approx(0.25));
    }
}
