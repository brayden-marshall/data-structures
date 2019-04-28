#include "catch.h"
#include "../src/binary_search_tree.h"

#include <iostream>

TEST_CASE("Testing Binary Search Tree (BST) with int") {
    BST<int> tree;

    // testing insert
    tree.insert(5);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);

    CHECK(tree.contains(5));
    CHECK(tree.contains(2));
    CHECK(tree.contains(6));
    CHECK(tree.contains(1));

    SECTION("Testing node removal cases") {
        tree.insert(3);
        tree.insert(4);
        tree.insert(0);
        REQUIRE(tree.contains(3));
        REQUIRE(tree.contains(4));
        REQUIRE(tree.contains(0));
        /* tree should look like
         *          5
         *         / \
         *        2   6
         *       / \
         *      1   3
         *     /     \
         *    0       4
         */

        SECTION("Removing node with zero children") {
            tree.remove(6);
            CHECK(!tree.contains(6));
        }

        SECTION("Removing node with only a right child") {
            tree.remove(3);
            CHECK(!tree.contains(3));
        }

        SECTION("Removing node with only a left child") {
            tree.remove(1);
            CHECK(!tree.contains(1));
        }

        SECTION("Removing node with two children") {
            tree.remove(2);
            CHECK(!tree.contains(2));
        }
    }

}
