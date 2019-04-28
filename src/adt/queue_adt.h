#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H

#include "../linked_list.h"

/* Generic Queue implemented using a linked list
 */
template <typename T>
class IQueue {
    public:
        virtual ~IQueue() {}

        virtual void enque(const T &data) = 0;
        virtual T deque() = 0;
        virtual int size() const = 0;
        virtual bool is_empty() const = 0;
        virtual T front() const = 0;
        virtual T back() const = 0;
        virtual void clear() = 0;
};

#endif
