#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"
#include "adt/map_adt.h"

/* AVL tree (self balancing tree) implementation
 * Most of the interface functions are defined in the BST class
 * The overridden functions only add on the self-balancing
 * functionality
 */
template <typename K, typename V=K>
class AVLTree : public BST<K,V>,
                public virtual IMap<K,V> {
    protected:

        class Node : public BST<K,V>::Node {
            public:
                int balance_factor;
                Node(const K& key, const V* val, Node* parent=nullptr)
                    : BST<K,V>::Node(key, val, parent), balance_factor(0)
                {
                }
        };

    public:

        void insert(const K&) override;
        void insert(const K&, const V&) override;
        void remove(const K&) override;
};

template <typename K, typename V>
void AVLTree<K,V>::insert(const K& key) {
    BST<K,V>::insert(key);
}

template <typename K, typename V>
void AVLTree<K,V>::insert(const K& key, const V& val) {
    BST<K,V>::insert(key, val);
}

template <typename K, typename V>
void AVLTree<K,V>::remove(const K& key) {
    BST<K,V>::remove(key);
}

#endif
