#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

template <typename T>
class IPriorityQueue {
    public:
        virtual ~IPriorityQueue() {}

        virtual void push(const T&, int) = 0;
        virtual T pop() = 0;
        virtual T peek() const = 0;
        virtual bool is_empty() const = 0;
        virtual int size() const = 0;
};

#endif
