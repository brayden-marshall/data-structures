#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

/* Generic Stack implemented using a linked list
 */
template <typename T>
class Stack {
    private:
        LinkedList<T> linked_list;
    public:
        Stack() {}

        ~Stack() {}

        void push(const T &data) { linked_list.push_front(data); }

        T pop() { return linked_list.pop_front(); }

        T peek() { return linked_list.front(); }

        int size() { return linked_list.size(); }

        bool isEmpty() { return linked_list.isEmpty(); }

        void clear() { linked_list.clear(); }

        friend std::ostream& operator<<(std::ostream &out, const Stack &stack) {
            out << stack.linked_list;
            return out;
        }
};

#endif
