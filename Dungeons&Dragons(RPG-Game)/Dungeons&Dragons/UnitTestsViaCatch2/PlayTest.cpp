#define CATCH_CONFIG_MAIN
#include "E:\catch2.hpp"
#include "Play.hpp"

TEST_CASE("Play constructor and gamePlay method", "Play") {
    SECTION("Invalid maze file") {
        REQUIRE_THROWS_AS(Play("mazeTestInvalid.txt"), std::runtime_error);
    }
}
