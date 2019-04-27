#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <cassert>

/* generic singly-linked list implementation
 * operations:
 *   isEmpty() - O(1)
 *   size() - O(1)
 *   front() - O(1)
 *   back() - O(1)
 *   push_back() - O(1)
 *   push_front() - O(1)
 *   pop_back() - O(N)
 *      - pop_back is O(N) due to the singly-linked implementation
 *   pop_front() - O(1)
 *   remove(data) - O(N)
 *   clear() - O(N)
 *
 */
template <typename T>
class LinkedList {
    protected:
        struct Node {
            T data;
            Node* next;
            Node(const T &data, Node* next = nullptr) : data(data), next(next)
            {
            }
        };


        Node* m_head;
        Node* m_tail;
        int m_size;

    public:
        LinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {
        }

        ~LinkedList() {
            this->clear();
        }

        // interface methods
        bool isEmpty() const { return this->m_size == 0; }

        int size() const { return this->m_size; }

        T front() const {
            if (this->isEmpty()) {
                throw "EXCEPTION: front() called on empty list.";
            }
            return m_head->data;
        }

        T back() const {
            if (this->isEmpty()) {
                throw "EXCEPTION: back() called on empty list.";
            }
            return m_tail->data;
        }

        void push_back(const T &data) {
            Node *new_node = new Node(data);
            if (this->isEmpty()) {
                m_head = new_node;
                m_tail = new_node;
            } else {
                m_tail->next = new_node;
                m_tail = new_node;
            }
            m_size++;
        }

        void push_front(const T &data) {
            m_head = new Node(data, m_head);
            if (m_tail == nullptr) {
                m_tail = m_head;
            }
            m_size++;
        }

        T pop_back() {
            // back() takes care of empty list case
            T data = back();

            if (m_size == 1) {
                delete m_head;
                m_head = m_tail = nullptr;
            } else {
                Node* current_node = m_head;
                while (current_node->next != m_tail) {
                    current_node = current_node->next;
                }
                delete m_tail;
                m_tail = current_node;
                m_tail->next = nullptr;
            }
            m_size--;
            return data;
        }

        T pop_front() {
            T data = this->front();
            // need a temp pointer to head for memory deallocation
            Node* temp_node = m_head;
            m_head = m_head->next;
            delete temp_node;

            m_size--; 
            return data;
        }

        void remove(T data) {
            if (this->isEmpty()) {
                throw "EXCEPTION: remove on empty list.";
            }

            // shortcut to handle case of size == 1
            if (m_head->data == data) {
                pop_front();
                return;
            }

            Node* current_node = m_head;
            while (current_node->next != nullptr) {
                // if next node matches function argument, remove that node
                if (current_node->next->data == data) {
                    // need a temp pointer to deallocate memory after moving next pointers
                    Node* temp_ptr = current_node;
                    current_node->next = current_node->next->next;
                    delete current_node;
                }
                current_node = current_node->next;
            }
            m_size--;
        }

        void clear() {
            // loop through, and delete, every node
            while (m_head != nullptr) {
                Node* temp = m_head;
                m_head = m_head->next;
                delete temp;
            }

            // reset list to an empty state
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
        }

        // overloaded operators
        friend std::ostream& operator<<(std::ostream &out, const LinkedList &list) {
            out << "[";
            Node* current_node = list.m_head;
            while (current_node != nullptr) {
                out << current_node->data;
                if (current_node->next != nullptr) {
                    out << ", ";
                }
                current_node = current_node->next;
            }
            out << "]";
            return out;
        }
};

#endif
