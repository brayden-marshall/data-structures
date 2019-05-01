#ifndef SET_ADT_H
#define SET_ADT_H

template <typename T>
class ISet {
    public:
        virtual ~ISet() {}

        virtual void insert(const T&) = 0;
        virtual void remove(const T&) = 0;
        virtual bool contains(const T&) const = 0;
        virtual bool is_empty() const = 0;
        virtual int size() const = 0;
};

#endif
