#ifndef MAP_ADT_H
#define MAP_ADT_H

template <typename K, typename V>
class IMap {
    public:
        virtual ~IMap() {}

        virtual void set(const K&, const V&) = 0;
        virtual void remove(const K&) = 0;
        virtual const V& at(const K&) const = 0;
        virtual bool contains(const K&) const = 0;
        virtual bool is_empty() const = 0;
        virtual int size() const = 0;
};

#endif
