#ifndef MAP_ADT_H
#define MAP_ADT_H

template <typename K, typename V>
class IMap {
    public:
        virtual ~IMap() {}

        virtual void set(const K& data) = 0;
        virtual V remove(const K& data) = 0;
        virtual const V& find(const K& data) const = 0;
        virtual bool isEmpty() const = 0;
        virtual int size() const = 0;
};

#endif
