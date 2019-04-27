#include "catch.h"
#include "../src/stack.h"

TEST_CASE("Testing Stack") {
    Stack<int> stack;
    
    CHECK(stack.size() == 0);
    CHECK(stack.isEmpty());

    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }

    CHECK(stack.size() == 10);
    CHECK(!stack.isEmpty());
    CHECK(stack.peek() == 9);

    CHECK(stack.pop() == 9);
    CHECK(stack.pop() == 8);
    CHECK(stack.pop() == 7);

    stack.clear();
    
    CHECK(stack.size() == 0);
    CHECK(stack.isEmpty());
}
