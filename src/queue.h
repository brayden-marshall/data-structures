#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

/* Generic Queue implemented using a linked list
 */
template <typename T>
class Queue {
    private:
        LinkedList<T> linked_list;
    public:
        Queue() {}

        ~Queue() {}

        void push(const T &data) { linked_list.push_back(data); }

        T pop() { return linked_list.pop_front(); }

        int size() const { return linked_list.size(); }

        bool isEmpty() const { return linked_list.isEmpty(); }

        T front() const { return linked_list.front(); }

        T back() const { return linked_list.back(); }

        void clear() { linked_list.clear(); }

        friend std::ostream& operator<<(std::ostream &out, const Queue &q) {
            out << q.linked_list;
            return out;
        }
};

#endif
