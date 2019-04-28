#include <string>

#include "../catch.h"
#include "../../src/hash_table.h"

TEMPLATE_TEST_CASE("Testing Map with int, string", "[map][adt]",
                  (HashTable<int, std::string>)) {
    TestType map_;
    IMap<int, std::string>* map = &map_;

    REQUIRE(map->isEmpty());
    REQUIRE(map->size() == 0);
}
