#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "adt/priority_queue_adt.h"

/* Binary Heap implemented with an array
 * Elements with higher priority are served first
 */
template <typename T>
class BinaryHeap : public virtual IPriorityQueue<T> {
    protected:
        struct Element {
            T data;
            int priority;
            Element(const T& data, const int priority) : data(data), priority(priority) 
            {
            }
        };

        std::vector<Element> m_arr;

        int parent_index(int) const;
        int left_child_index(int) const;
        int right_child_index(int) const;
        int min_child_index(int, int);
        void sift_up(int);
        void sift_down(int);
        void print() const;

    public:
        
        virtual void push(const T&, int) override;
        virtual T pop() override;
        virtual T peek() const override;
        virtual bool is_empty() const override;
        virtual int size() const override;

};

/******************************
 * Protected Member Functions *
 *****************************/
template <typename T>
int BinaryHeap<T>::parent_index(int index) const {
    return (index - 1) / 2;
}

template <typename T>
int BinaryHeap<T>::left_child_index(int index) const {
    return (2 * index) + 1;
}

template <typename T>
int BinaryHeap<T>::right_child_index(int index) const {
    return (2 * index) + 2;
}

// recursively swaps child and parent to maintain heap property
// teriminates when parent is root, or parent is already greater than child
template <typename T>
void BinaryHeap<T>::sift_up(int child) {
    int parent = parent_index(child);

    // base case
    if (child == 0) {
        return;
    }

    // if child's priority is larger than parent's, swap them and sift up
    if (m_arr[child].priority > m_arr[parent].priority) {
        std::swap(m_arr[child], m_arr[parent]);
        sift_up(parent);
    }
}

// assumes at least one of left and right is in bounds
template <typename T>
int BinaryHeap<T>::min_child_index(int left, int right) {
    assert(left < size() || right < size());

    if (left < size() && right < size()) {
        return m_arr[left].priority > m_arr[right].priority
            ? left : right;
    } else if (right < size()) {
        return right;
    } else {
        return left;
    }
}

template <typename T>
void BinaryHeap<T>::sift_down(int parent) {
    int left_child = left_child_index(parent);
    int right_child = right_child_index(parent);

    // base case, parent has no children
    if (left_child >= size() && right_child > size()) {
        return;
    }

    int largest_child = min_child_index(left_child, right_child);

    if (m_arr[parent].priority < m_arr[largest_child].priority) {
        std::swap(m_arr[parent], m_arr[largest_child]);
        sift_down(largest_child);
    }
}

// debug function that prints values of the underlying vector
template <typename T>
void BinaryHeap<T>::print() const {
    for (auto val : m_arr) {
        std::cout << val.data << "->" << val.priority << std::endl;
    }
    std::cout << "**********************\n";
}

/***************************
 * Public Member Functions *
 **************************/
template<typename T>
void BinaryHeap<T>::push(const T& data, int priority) {
    m_arr.push_back(Element(data, priority));
    sift_up(m_arr.size()-1);
}

// throws an exception when called on an empty heap
template<typename T>
T BinaryHeap<T>::pop() {
    T data = peek();

    m_arr[0] = m_arr.back();
    m_arr.pop_back();

    sift_down(0);
    return data;
} 

// throws an exception when called on an empty heap
template<typename T>
T BinaryHeap<T>::peek() const {
    if (is_empty()) {
        throw std::runtime_error("Cannot pop from empty heap");
    }
    return m_arr.front().data;
}

template<typename T>
bool BinaryHeap<T>::is_empty() const {
    return m_arr.empty();
}

template<typename T>
int BinaryHeap<T>::size() const {
    return m_arr.size();
}

#endif
