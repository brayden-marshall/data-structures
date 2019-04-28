#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "adt/map_adt.h"

template <typename K, typename V>
class HashTable : public virtual IMap<K, V> {
    protected:
        int m_size;
    public:
        HashTable() : m_size(0) {
        }

        virtual ~HashTable() {
        }

        virtual void set(const K& data) override;
        virtual V remove(const K& data) override;
        virtual const V& find(const K& data) const override;
        virtual bool isEmpty() const override;
        virtual int size() const override;
};

template <typename K, typename V>
void HashTable<K, V>::set(const K& data) {
}

template <typename K, typename V>
V HashTable<K, V>::remove(const K& data) {
    return V{};
}

template <typename K, typename V>
const V& HashTable<K, V>::find(const K& data) const {
    return V{};
}

template <typename K, typename V>
bool HashTable<K, V>::isEmpty() const {
    return m_size == 0;
}

template <typename K, typename V>
int HashTable<K, V>::size() const {
    return m_size;
}

#endif
