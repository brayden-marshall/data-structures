#include "../catch.h"
#include "../../src/adt/set_adt.h"
#include "../../src/binary_search_tree.h"

TEMPLATE_TEST_CASE("Testing set ADT with int", "[adt][set]", BST<int>) {
    TestType tree;
    ISet<int>* set = &tree;
    REQUIRE(set->is_empty());
    REQUIRE(set->size() == 0);

    SECTION("Testing insert and remove 1 item") {
        set->insert(1);

        CHECK(set->contains(1));
        CHECK(!set->is_empty());
        CHECK(set->size() == 1);

        set->remove(1);

        CHECK(!set->contains(1));
        CHECK(set->is_empty());
        CHECK(set->size() == 0);
    }

    SECTION("Testing insert and remove 10 items") {
        for (int i = 0; i < 10; i++) {
            set->insert(i);
        }

        for (int i = 0; i < 10; i++) {
            CHECK(set->contains(i));
            set->remove(i);
            CHECK(!set->contains(i));
        }
    }
}
