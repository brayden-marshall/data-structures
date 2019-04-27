#include "catch.h"
#include "../src/queue.h"

#include <iostream>

TEST_CASE("Testing Queue") {
    Queue<int> que;
    CHECK(que.size() == 0);
    CHECK(que.isEmpty());

    for (int i = 0; i < 10; i++) {
        que.push(i);
    }

    CHECK(que.size() == 10);
    CHECK(!que.isEmpty());
    CHECK(que.front() == 0);
    CHECK(que.back() == 9);

    CHECK(que.pop() == 0);
    CHECK(que.pop() == 1);
    CHECK(que.pop() == 2);

    que.clear();

    CHECK(que.size() == 0);
    CHECK(que.isEmpty());
}
