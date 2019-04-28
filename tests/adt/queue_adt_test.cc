#include "../catch.h"
#include "../../src/linked_list.h"

TEMPLATE_TEST_CASE("Testing Queue with int", "[queue][adt]", LinkedList<int>) {
    TestType que_;
    IQueue<int>* que = &que_;
    CHECK(que->size() == 0);
    CHECK(que->isEmpty());

    for (int i = 0; i < 10; i++) {
        que->enque(i);
    }

    CHECK(que->size() == 10);
    CHECK(!que->isEmpty());
    CHECK(que->front() == 0);
    CHECK(que->back() == 9);

    CHECK(que->deque() == 0);
    CHECK(que->deque() == 1);
    CHECK(que->deque() == 2);

    que->clear();

    CHECK(que->size() == 0);
    CHECK(que->isEmpty());
}
