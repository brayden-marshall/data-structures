#include "../catch.h"
#include "../../src/linked_list.h"

TEMPLATE_TEST_CASE("Testing Stack with int", "[stack][adt]", LinkedList<int>) {
    TestType stack_;
    IStack<int>* stack = &stack_;
    
    CHECK(stack->size() == 0);
    CHECK(stack->isEmpty());

    for (int i = 0; i < 10; i++) {
        stack->push(i);
    }

    CHECK(stack->size() == 10);
    CHECK(!stack->isEmpty());
    CHECK(stack->peek() == 9);

    CHECK(stack->pop() == 9);
    CHECK(stack->pop() == 8);
    CHECK(stack->pop() == 7);

    stack->clear();
    
    CHECK(stack->size() == 0);
    CHECK(stack->isEmpty());
}
