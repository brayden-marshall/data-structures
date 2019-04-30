#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory> // for unique_ptr
#include <stdexcept>

#include "adt/map_adt.h"

/* Binary Search Tree implementation
 * This is a basic binary search tree that does not self-balance
 * It is meant to provide common base class functionality that can
 * be extended into implementations such as AVL trees and red/black
 * trees
 */
template <typename K, typename V=K>
class BST : public virtual IMap<K, V> {
    protected:
        /* Each parent node uniquely owns it's children
         * Node's parent pointers are observers and do not own anything
         */
        class Node {
            public:
                K key;
                std::unique_ptr<V> val;
                Node* parent;
                std::unique_ptr<Node> left;
                std::unique_ptr<Node> right;
                Node(const K& key, const V* val, Node* parent=nullptr) 
                    : key(key), parent(parent), left(nullptr), right(nullptr)
                {
                    this->val = val == nullptr ? nullptr : std::make_unique<V>(*val);
                }

                Node(const K& key, Node* parent=nullptr)
                    : Node(key, nullptr, parent)
                {
                }
        };

        std::unique_ptr<Node> root_;
        int size_;

        void bst_insert(Node*, const K&, const V* val=nullptr);
        Node* bst_find(const K&, Node*) const;
        void bst_remove(const K&, Node*);
        void replace_node_with_child(Node*, std::unique_ptr<Node> child=nullptr);
        Node* find_min(Node* node) const;

    public:
        BST() : root_(nullptr), size_(0) {}
        virtual ~BST() {}

        // standard BST operations
        virtual bool contains(const K&) const override;
        void insert(const K&);
        void insert(const K&, const V&);
        virtual void remove(const K&) override;

        // IMap ADT wrapppers
        virtual void set(const K& key, const V& val) override;
        virtual const V& at(const K& key) const override;
        virtual bool is_empty() const;
        virtual int size() const;
};

/********************
 * Map ADT Wrappers *
 *******************/
template <typename K, typename V>
void BST<K,V>::set(const K& key, const V& val) {
    insert(key, val);
}

template <typename K, typename V>
const V& BST<K,V>::at(const K& key) const {
    auto val = bst_find(key, root_.get())->val.get();
    if (val == nullptr) {
        throw std::runtime_error("Key does not exist");
    }
    return *val;
}

template <typename K, typename V>
bool BST<K,V>::is_empty() const {
    return size_ == 0;
}

template <typename K, typename V>
int BST<K,V>::size() const {
    return size_;
}

/***************************
 * Public Member Functions *
 **************************/

template <typename K, typename V>
bool BST<K,V>::contains(const K& key) const {
    return bst_find(key, root_.get()) != nullptr;
}

template <typename K, typename V>
void BST<K,V>::insert(const K& key) {
    bst_insert(root_.get(), key);
    size_++;
}

template <typename K, typename V>
void BST<K,V>::insert(const K& key, const V& val) {
    bst_insert(root_.get(), key, &val);
    size_++;
}

template <typename K, typename V>
void BST<K, V>::remove(const K& key) {
    bst_remove(key, root_.get());
    size_--;
}

/******************************
 * Protected Member Functions *
 *****************************/

// FIXME: this may be more complex than need be due to my unfamiliarity 
// with unique_ptr, refactor if possible
template <typename K, typename V>
void BST<K, V>::bst_insert(Node* node, const K& key, const V* val) {
    if (node == nullptr) {
        root_ = std::make_unique<Node>(key, val);
        return;
    }

    if (key < node->key) {
        if (node->left == nullptr) {
            node->left = std::make_unique<Node>(key, val, node);
        } else {
            bst_insert(node->left.get(), key, val);
        }
    } else if (key > node->key) {
        if (node->right == nullptr) {
            node->right = std::make_unique<Node>(key, val, node);
        } else {
            bst_insert(node->right.get(), key, val);
        }
    }
}

/* Protected recursive function that finds a node that matches a given key.
 * Returns:
 *   - the node containing 'key', if exists
 *   - null if 'key' does not exist in tree
 */
template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::bst_find(const K &key, Node* node) const {
    // base case
    // handles key not found at leaf, or key found at any node
    if (node == nullptr || node->key == key) {
        return node;
    }
    
    // recursive case calls find on left and right of 'node'
    Node* node_found = bst_find(key, node->left.get());
    if (node_found != nullptr) {
        return node_found;
    }
    return bst_find(key, node->right.get());
}

/* Protected recursive function that removes a node matching a given key.
 * Time Complexity:
 *   O(logN) for bst_find operation + O(1) for removal
 *   O(logN) overall
 */
template <typename K, typename V>
void BST<K, V>::bst_remove(const K& key, Node* node) {
    node = bst_find(key, node);

    if (node->left != nullptr && node->right != nullptr) {

        // replace node with it's successor and call remove the old successor node
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
template <typename K, typename V>
void BST<K, V>::replace_node_with_child(Node* node, std::unique_ptr<Node> child) {
    // set child's pointer to node's parent
    if (child != nullptr) {
        child->parent = node->parent;
    }

    // special case for node == root because root's parent is nullptr
    if (node->key == root_->key) {
      root_ = std::move(child);
    } else {
      // update node's parent's left or right pointer
      if (node == node->parent->left.get()) {
          node->parent->left = std::move(child);
      } else if (node == node->parent->right.get()) {
          node->parent->right = std::move(child);
      }
    }
}

// Finds the left-most descendant of a node
template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::find_min(Node* node) const {
    while (node->left != nullptr) {
        node = node->left.get();
    }
    return node;
}

#endif
