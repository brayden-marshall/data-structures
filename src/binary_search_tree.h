#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory> // for unique_ptr

/* Node class used in Binary Search Tree implementation
 * Each parent node uniquely owns it's children
 * Node's parent pointers are observers and do not own anything
 */
template <typename K>
class Node {
    public:
        std::unique_ptr<Node<K>> left;
        std::unique_ptr<Node<K>> right;
        Node<K>* parent;
        K key;
        Node(const K& key, Node<K>* parent=nullptr) 
            : key(key), parent(parent), left(nullptr), right(nullptr)
        {
        }
};

/* Binary Search Tree implementation
 * This is a basic binary search tree that does not self-balance
 * It is meant to provide common base class functionality that can
 * be extended into implementations such as AVL trees and red/black
 * trees
 */
template <typename K>
class BST {
    protected:
        std::unique_ptr<Node<K>> root;

        void bst_insert(const K&, Node<K>*);
        Node<K>* bst_find(const K&, Node<K>*) const;
        void bst_remove(const K&, Node<K>*);
        void replace_node_with_child(Node<K>*, std::unique_ptr<Node<K>> child=nullptr);
        Node<K>* find_min(Node<K>* node) const;

    public:
        BST() : root(nullptr) {}

        bool contains(const K& data) const { return bst_find(data, root.get()) != nullptr; }
        void insert(const K& data) { bst_insert(data, root.get()); }
        void remove(const K& data) { bst_remove(data, root.get()); }
};

// FIXME: this may be more complex than need be due to my unfamiliarity 
// with unique_ptr, refactor if possible
template <typename K>
void BST<K>::bst_insert(const K& key, Node<K>* node) {
    if (node == nullptr) {
        root = std::make_unique<Node<K>>(key);
        return;
    }

    if (key < node->key) {
        if (node->left == nullptr) {
            node->left = std::make_unique<Node<K>>(key, node);
        } else {
            bst_insert(key, node->left.get());
        }
    } else if (key > node->key) {
        if (node->right == nullptr) {
            node->right = std::make_unique<Node<K>>(key, node);
        } else {
            bst_insert(key, node->right.get());
        }
    }
}

/* Private recursive function that finds a node that matches a given key.
 * Time Complexity:
 *   O(logN) (binary search)
 * Returns:
 *   - the node containing 'key', if exists
 *   - null if 'key' does not exist in tree
 */
template <typename K>
Node<K>* BST<K>::bst_find(const K &key, Node<K>* node) const {
    // base case
    // handles key not found at leaf, or key found at any node
    if (node == nullptr || node->key == key) {
        return node;
    }
    
    // recursive case calls find on left and right of 'node'
    Node<K>* node_found = bst_find(key, node->left.get());
    if (node_found != nullptr) {
        return node_found;
    }
    return bst_find(key, node->right.get());
}

/* Private, recursive helper function that removes a node matching a given key.
 * Time Complexity:
 *   O(logN) for bst_find operation + O(1) for removal
 *   O(logN) overall
 */
template <typename K>
void BST<K>::bst_remove(const K& key, Node<K>* node) {
    node = bst_find(key, node);

    if (node->left != nullptr && node->right != nullptr) {

        auto successor = find_min(node->right.get());
        K temp_key = successor->key;
        bst_remove(successor->key, successor);
        node->key = temp_key;

    } else if (node->left != nullptr) {
        replace_node_with_child(node, std::move(node->left));
    } else if (node->right != nullptr) {
        replace_node_with_child(node, std::move(node->right));
    } else {
        replace_node_with_child(node);
    }
}

/* Private helper function to assist bst_remove.
 * Replaces a node with it's child, and updates all affected pointers
 * Args:
 *   node:
 *     A Node to be removed which has 0 or 1 children
 *   child:
 *     node's child, nullptr if node has 0 children
 */
template <typename K>
void BST<K>::replace_node_with_child(Node<K>* node, std::unique_ptr<Node<K>> child) {
    // set child's pointer to node's parent
    if (child != nullptr) {
        child->parent = node->parent;
    }

    // update node's parent's left or right pointer
    if (node == node->parent->left.get()) {
        node->parent->left = std::move(child);
    } else if (node == node->parent->right.get()) {
        node->parent->right = std::move(child);
    }
}

// Finds the left-most descendant of a node
template <typename K>
Node<K>* BST<K>::find_min(Node<K>* node) const {
    while (node->left != nullptr) {
        node = node->left.get();
    }
    return node;
}

#endif
