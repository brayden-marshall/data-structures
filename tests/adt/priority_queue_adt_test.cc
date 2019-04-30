#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

#include "../catch.h"
#include "../../src/adt/priority_queue_adt.h"
#include "../../src/binary_heap.h"

int get_random_int(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

TEMPLATE_TEST_CASE("Testing priority queue with int", "[adt][priority-queue]", BinaryHeap<int>) {
    // setting up random number seed
    srand(static_cast<unsigned int>(time(0)));
    rand();

    TestType que_;
    IPriorityQueue<int>* que = &que_;

    REQUIRE(que->is_empty());
    REQUIRE(que->size() == 0);
    CHECK_THROWS(que->pop());
    CHECK_THROWS(que->peek());

    SECTION("Testing push/pop on small set of data") {
        // testing push
        que->push(7, 1);

        CHECK(que->size() == 1);
        CHECK(que->pop() == 7);

        que->push(8, 4);
        que->push(3, 2);
        que->push(9, 2);
        que->push(1, 10);

        CHECK(que->size() == 4);
        CHECK(! que->is_empty());

        // testing that pop matches expected priority sequence
        CHECK(que->pop() == 1);
        CHECK(que->size() == 3);

        CHECK(que->pop() == 8);
        // elements with the same priority will come out in undefined order
        {
            auto data = que->pop(); 
            CHECK((data == 3 || data == 9));
            data = que->pop();
            CHECK((data == 3 || data == 9));
        }
        CHECK(que->is_empty());
    }

    SECTION("Testing push/pop on large set of generated data") {
        const int data_size = 100;
        for (int i = 0; i < data_size; i++) {
            que->push(i, data_size-i);
        }

        for (int i = 0; i < data_size; i++) {
            CHECK(que->pop() == i);
        }
    }
}
