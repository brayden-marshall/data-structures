#include "catch.h"
#include "../src/linked_list.h"

TEST_CASE("Testing LinkedList") {
    LinkedList<int> list;

    CHECK(list.size() == 0);
    CHECK(list.isEmpty());


    // testing push methods
    list.push_back(1);
    list.push_front(2);

    CHECK(list.size() == 2);
    CHECK(! list.isEmpty());
    CHECK(list.front() == 2);
    CHECK(list.back() == 1);

    // testing remove
    list.remove(2);

    CHECK(list.size() == 1);
    CHECK(! list.isEmpty());
    CHECK(list.front() == list.back());
    CHECK(list.front() == 1);

    // testing push and remove with more data
    list.clear();
    for (int i = 0; i < 20; i++) {
        list.push_back(i);
    }

    CHECK(list.size() == 20);
    CHECK(list.front() == 0);
    CHECK(list.back() == 19);
}
