#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Spell.hpp"

TEST_CASE("Spell class tests", "Spell") {
    Spell spell("Fireball", 0.3);

    SECTION("Clone creates a correct copy") {
        Spell* cloned_spell = spell.clone();
        REQUIRE(cloned_spell->getName() == "Fireball");
        REQUIRE(cloned_spell->getParam() == Approx(0.3));
        delete cloned_spell;
    }

    SECTION("getParam returns correct bonus mana value") {
        REQUIRE(spell.getParam() == Approx(0.3));
    }
}
