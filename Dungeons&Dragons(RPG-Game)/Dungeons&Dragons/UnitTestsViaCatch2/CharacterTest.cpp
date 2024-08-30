#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Human.hpp"
#include "Weapon.hpp"
#include "Armour.hpp"
#include "Spell.hpp"

TEST_CASE("Human class tests", "Human") {
    Human human(100, 10, 50);

    SECTION("Initial values are set correctly") {
        REQUIRE(human.getHealth() == 100);
        REQUIRE(human.getDamage() == 10);
        REQUIRE(human.getMana() == 50);
    }

    SECTION("Clone creates a correct copy") {
        Human *copy = human.clone();
        REQUIRE(copy->getHealth() == human.getHealth());
        REQUIRE(copy->getDamage() == human.getDamage());
        REQUIRE(copy->getMana() == human.getMana());
        delete copy;
    }

    SECTION("Add and remove items from inventory") {
        human.addItemToInventory(new Armour("Shield", 0.25));

        REQUIRE(human.getInventory().getItems().size() == 3);

        human.removeItem(human.getInventory().getItems().front());
        REQUIRE(human.getInventory().getItems().size() == 2);
    }

    SECTION("Take damage reduces health correctly") {
        human.takeDamage(20);
        REQUIRE(human.getHealth() == 80);

        human.addItemToInventory(new Armour("Shield", 0.25));
        human.takeDamage(20);
        REQUIRE(human.getHealth() == 65);
    }

    SECTION("Deal damage via attack") {
        Human enemy(100, 10, 50);

        human.addItemToInventory(new Weapon("Sword", 0.5));
        human.dealDamageViaAttack(enemy);
        REQUIRE(enemy.getHealth() == 82.0);
    }

    SECTION("Deal damage via spell") {
        Human enemy(100, 10, 50);

        human.addItemToInventory(new Spell("Fireball", 0.3));
        human.dealDamageViaSpell(enemy);
        REQUIRE(enemy.getHealth() == 22.0);
    }

    SECTION("Heal increases health correctly") {
        human.takeDamage(50);
        human.heal(30);
        REQUIRE(human.getHealth() == 80);
    }

    SECTION("Bleed reduces health correctly") {
        human.bleed(20);
        REQUIRE(human.getHealth() == 80);
    }
}
