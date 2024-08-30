#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Inventory.hpp"
#include "Weapon.hpp"
#include "Armour.hpp"

TEST_CASE("Inventory class tests", "Inventory") {
    Inventory inventory;

    Weapon sword("Sword", 0.5);
    Armour shield("Shield", 0.25);

    SECTION("Add items to inventory") {
        inventory.addItem(&sword);
        inventory.addItem(&shield);

        REQUIRE(inventory.getItems().size() == 2);
        REQUIRE(inventory.getItems()[0]->getName() == "Sword");
        REQUIRE(inventory.getItems()[1]->getName() == "Shield");
    }

    SECTION("Remove items from inventory") {
        inventory.addItem(&sword);
        inventory.addItem(&shield);

        inventory.removeItem(&sword);

        REQUIRE(inventory.getItems().size() == 1);
        REQUIRE(inventory.getItems()[0]->getName() == "Shield");
    }

    SECTION("Clear inventory") {
        inventory.addItem(&sword);
        inventory.addItem(&shield);

        inventory.clearInvenotry();

        REQUIRE(inventory.getItems().empty());
    }

    SECTION("Copy constructor creates a correct copy") {
        inventory.addItem(&sword);
        inventory.addItem(&shield);

        Inventory copy = inventory;

        REQUIRE(copy.getItems().size() == 2);
        REQUIRE(copy.getItems()[0]->getName() == "Sword");
        REQUIRE(copy.getItems()[1]->getName() == "Shield");
    }

    SECTION("Assignment operator creates a correct copy") {
        inventory.addItem(&sword);
        inventory.addItem(&shield);

        Inventory copy;
        copy = inventory;

        REQUIRE(copy.getItems().size() == 2);
        REQUIRE(copy.getItems()[0]->getName() == "Sword");
        REQUIRE(copy.getItems()[1]->getName() == "Shield");
    }
}
