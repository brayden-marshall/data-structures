#include <string>

#include "../catch.h"
#include "../../src/adt/map_adt.h"

/*
TEMPLATE_TEST_CASE("Testing Map with int, string", "[map][adt]") {
    TestType map_;
    IMap<int, std::string>* map = &map_;

    REQUIRE(map->is_empty());
    REQUIRE(map->size() == 0);

    SECTION("Testing .set() and .at()") {
        map->set(7, "Seven");

        CHECK(!map->is_empty());
        CHECK(map->size() == 1);
        CHECK(map->at(7) == "Seven");

        map->set(100, "One Hundred");
        map->set(42, "Forty Two");
        map->set(13, "Thirteen");

        CHECK(map->size() == 4);
        CHECK(map->at(100) == "One Hundred");
        CHECK(map->at(42) == "Forty Two");
        CHECK(map->at(13) == "Thirteen");
    }
}
*/
