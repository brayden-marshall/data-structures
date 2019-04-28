#ifndef STACK_ADT_H
#define STACK_ADT_H

template <typename T>
class IStack {
    public:
        virtual ~IStack() {}
        virtual void push(const T&) = 0;
        virtual T pop() = 0;
        virtual T peek() const = 0;
        virtual int size() const = 0;
        virtual bool isEmpty() const = 0;
        virtual void clear() = 0;
};

#endif
