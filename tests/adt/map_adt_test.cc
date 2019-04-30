#include <string>

#include "../catch.h"
#include "../../src/adt/map_adt.h"
#include "../../src/binary_search_tree.h"

TEMPLATE_TEST_CASE("Testing Map with int, string", "[map][adt]", (BST<int, std::string>)) {
    TestType map_;
    IMap<int, std::string>* map = &map_;

    REQUIRE(map->is_empty());
    REQUIRE(map->size() == 0);

    SECTION("Testing .set() and .at() on small data set") {
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

        SECTION("Testing .remove()") {
            map->remove(7);
            CHECK(!map->contains(7));
            CHECK(map->contains(100));
            CHECK(map->contains(42));
            CHECK(map->contains(13));
        }
    }

    SECTION("Testing .set() and .at() on large generated data") {
        const int data_size = 100;
        for (int i = 0; i < data_size; i++) {
            map->set(i, std::to_string(i));
        }

        for (int i = 0; i < data_size; i++) {
            CHECK(map->at(i) == std::to_string(i));
        }
    }
}
