#include "catch.h"
#include "../src/linked_list.h"

#include <sstream>

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

    list.clear();
    for (int i = 0; i < 20; i++) {
        list.push_back(i);
    }

    CHECK(list.size() == 20);
    CHECK(list.front() == 0);
    CHECK(list.back() == 19);

    // testing operator<<
    std::ostringstream string_stream;
    string_stream << list;
    CHECK(string_stream.str() == 
          "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]");
}
