#ifndef BST_H
#define BST_H

template <typename K>
class BSTNode {
    public:
        BSTNode<K>* left;
        BSTNode<K>* right;
        BSTNode<K>* parent;
        K key;
        BSTNode(const K& key) 
            : key(key), parent(nullptr), left(nullptr), right(nullptr)
        {
        }
};

/* Generic Binary Search Tree
 * - does not allow duplicate values
 */
template <typename K>
class BST {
    protected:

        // member variables
        BSTNode<K>* root;

        // member functions
        BSTNode<K>* bst_find(const K &key, BSTNode<K>* node) const;
        BSTNode<K>* bst_insert(const K &key, BSTNode<K>*& node);
        void replace_node_with_child(BSTNode<K>* node, BSTNode<K>* child=nullptr);
        void bst_remove(const K &key, BSTNode<K>* node);
        BSTNode<K>* find_min(BSTNode<K>* node);
        void destroy(BSTNode<K>* node);

    public:
        BST() : root(nullptr) {} 

        virtual ~BST() { this->destroy(root); }

        bool contains(const K &key) const { return bst_find(key, root) != nullptr; }

        void insert(const K &key) { bst_insert(key, root); }

        void remove(const K &key) { bst_remove(key, root);    }
};

template <typename K>
BSTNode<K>* BST<K>::bst_find(const K &key, BSTNode<K>* node) const {
    // base case
    // handles key not found at leaf, or key found at any node
    if (node == nullptr || node->key == key) {
        return node;
    }
    
    // recursive case calls find on left and right of 'node'
    BSTNode<K>* node_found = bst_find(key, node->left);
    if (node_found != nullptr) {
        return node_found;
    }
    return bst_find(key, node->right);
}

// this method only returns a node to allow for setting the 
// new node's parent pointer
template <typename K>
BSTNode<K>* BST<K>::bst_insert(const K &key, BSTNode<K>*& node) {
    if (node == nullptr) {
        node = new BSTNode<K>(key);
    } else if (key < node->key) {
        BSTNode<K>* left_child = bst_insert(key, node->left);
        node->left = left_child;
        left_child->parent = node;
    } else if (key > node->key) {
        BSTNode<K>* right_child = bst_insert(key, node->right);
        node->right = right_child;
        right_child->parent = node;
    }
    return node;
}

template <typename K>
void BST<K>::bst_remove(const K &key, BSTNode<K>* node) {
    node = bst_find(key, node);

    if (node->left != nullptr && node->right != nullptr) {
        // get the successory to the current node
        BSTNode<K>* successor = find_min(node->right);

        // copy key of 'successor' to 'node'
        int temp_key = successor->key;

        // remove successor node, since it's values are now copied into another node
        bst_remove(successor->key, successor);
        node->key = temp_key;;

    } else if (node->left != nullptr) {
        replace_node_with_child(node, node->left);
    } else if (node->right != nullptr) {
        replace_node_with_child(node, node->right);
    } else {
        replace_node_with_child(node);
    }
}

/* this method is used to remove a node with 1 or 0 children
 * args:
 *     node = the node to remove
 *     child = the node's only child (nullptr if node has 0 children)
 */
template <typename K>
void BST<K>::replace_node_with_child(BSTNode<K>* node, BSTNode<K>* child) {
    // update node's parent's left or right pointer
    if (node == node->parent->right) {
        node->parent->right = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    }

    // set child's pointer to node's parent
    if (child != nullptr) {
        child->parent = node->parent;
    }

    delete node;
}

template <typename K>
BSTNode<K>* BST<K>::find_min(BSTNode<K>* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename K>
void BST<K>::destroy(BSTNode<K>* node) {
    if (node != nullptr) {
        if (node->left != nullptr) {
            destroy(node->left);
        }

        if (node->right != nullptr) {
            destroy(node->right);
        }

        delete node;
    }
}

#endif
