#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <stdexcept>
#include <memory> // for unique_ptr

#include "adt/stack_adt.h"
#include "adt/queue_adt.h"
#include "adt/list_adt.h"

/* Generic singly-linked list implementation
 * Every node is owned by the node behind it
 * Head pointer owns the first node
 * Tail does not own the node it points to
 * Operations:
 *   is_empty() - O(1)
 *   size() - O(1)
 *   front() - O(1)
 *   back() - O(1)
 *   push_back() - O(1)
 *   push_front() - O(1)
 *   pop_front() - O(1)
 *   remove(data) - O(N)
 *   clear() - O(N)
 */

template <typename T>
class LinkedList : public virtual IList<T>,
                   public virtual IStack<T>,
                   public virtual IQueue<T> {
    protected:
        struct Node {
            T data;
            std::unique_ptr<Node> next;
            Node(const T &data, Node* next = nullptr) : data(data), next(next)
            {
            }
        };

        std::unique_ptr<Node> m_head;
        Node* m_tail;
        int m_size;

    public:
        LinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {
        }

        virtual ~LinkedList() {
        }

        // interface methods
        virtual bool is_empty() const override;
        virtual int size() const override;
        virtual T front() const override;
        virtual T back() const override;
        virtual T get_at(const int index) const override;
        virtual void remove(const T&) override;
        virtual void clear() override;
        void push_back(const T&);
        void push_front(const T&);
        T pop_front();

        // Stack ADT methods
        virtual void push(const T& data) override {
            this->push_front(data);    
        }

        virtual T pop() override {
            return this->pop_front();
        }

        virtual T peek() const override {
            return this->front();
        }

        // Queue ADT methods
        virtual void enque(const T& data) override {
            return this->push_back(data);
        }

        virtual T deque() override {
            return this->pop_front();
        }

        friend std::ostream& operator<<(std::ostream &out, const LinkedList<T>& list) {
            out << "[";
            Node* current_node = list.m_head.get();
            while (current_node != nullptr) {
                out << current_node->data;
                if (current_node->next != nullptr) {
                    out << ", ";
                }
                current_node = current_node->next.get();
            }
            out << "]";
            return out;
        }
};

template <typename T>
bool LinkedList<T>::is_empty() const { 
    return this->m_size == 0;
}

template <typename T>
int LinkedList<T>::size() const {
    return this->m_size;
}

template <typename T>
T LinkedList<T>::front() const {
    if (this->is_empty()) {
        throw std::runtime_error("Cannot get front of an empty list");
    }
    return m_head->data;
}

template <typename T>
T LinkedList<T>::back() const {
    if (this->is_empty()) {
        throw std::runtime_error("Cannot get back of an empty list");
    }
    return m_tail->data;
}

template <typename T>
T LinkedList<T>::get_at(const int index) const {
    // bounds check
    if (index < 0 || index >= m_size) {
        throw std::runtime_error("Index out of bounds");
    }

    Node* current = m_head.get();
    for (int i = 0; i < index; i++) {
        current = current->next.get();
    }
    return current->data;
}

template <typename T>
void LinkedList<T>::push_back(const T& data) {
    if (this->is_empty()) {
        m_head = std::make_unique<Node>(data);
        m_tail = m_head.get();
    } else {
        m_tail->next = std::make_unique<Node>(data);
        m_tail = m_tail->next.get();
    }
    m_size++;
}

template <typename T>
void LinkedList<T>::push_front(const T &data) {

    auto temp = std::move(m_head);
    m_head = std::make_unique<Node>(data);
    m_head->next = std::move(temp);

    if (m_tail == nullptr) {
        m_tail = m_head.get();
    }
    m_size++;
}

template <typename T>
T LinkedList<T>::pop_front() {
    T data = this->front();
    m_head = std::move(m_head->next);

    m_size--; 
    return data;
}

template <typename T>
void LinkedList<T>::remove(const T& data) {
    if (this->is_empty()) {
        throw std::runtime_error("Cannot remove from empty list.");
    }

    // shortcut to handle case of size == 1
    if (m_head->data == data) {
        pop_front();
        return;
    }

    Node* current_node = m_head.get();
    while (current_node->next != nullptr) {
        // if next node matches function argument, remove that node
        if (current_node->next->data == data) {
            current_node->next = std::move(current_node->next->next);
        }
        current_node = current_node->next.get();
    }
    m_size--;
}

template <typename T>
void LinkedList<T>::clear() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

#endif
