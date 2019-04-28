#ifndef LIST_ADT_H
#define LIST_ADT_H

template <typename T>
class IList {
    public:
        virtual ~IList() {}

        virtual bool is_empty() const = 0;
        virtual void push_front(const T& data) = 0;
        virtual void push_back(const T& data) = 0;
        virtual T front() const = 0;
        virtual T back() const = 0;
        virtual T get_at(const int index) const = 0;
        virtual int size() const = 0;
        virtual void clear() = 0;
        virtual void remove(const T&) = 0;
};

#endif
