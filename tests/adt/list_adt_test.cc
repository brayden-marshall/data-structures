#include "../catch.h"
#include "../../src/linked_list.h"

TEMPLATE_TEST_CASE("Testing List with int", "[list][adt]", LinkedList<int>) {
    TestType list_;
    IList<int>* list = &list_;


    CHECK(list->size() == 0);
    CHECK(list->is_empty());

    // testing push methods
    list->push_back(1);
    list->push_front(2);

    CHECK(list->size() == 2);
    CHECK(! list->is_empty());
    CHECK(list->front() == 2);
    CHECK(list->back() == 1);

    // testing remove
    list->remove(2);

    CHECK(list->size() == 1);
    CHECK(! list->is_empty());
    CHECK(list->front() == list->back());
    CHECK(list->front() == 1);

    list->clear();
    for (int i = 0; i < 20; i++) {
        list->push_back(i);
    }

    CHECK(list->size() == 20);
    CHECK(list->front() == 0);
    CHECK(list->back() == 19);

    CHECK_THROWS(list->get_at(-1));
    CHECK_THROWS(list->get_at(20));
    CHECK(list->get_at(0) == 0);
    CHECK(list->get_at(19) == 19);
    CHECK(list->get_at(7) == 7);
}
