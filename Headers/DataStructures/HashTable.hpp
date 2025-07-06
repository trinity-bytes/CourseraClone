#include <vector>
#include <utility>// para std::pair

template <typename K, typename T>
class HashTable {
private:
    std::vector<std::vector<std::pair<K, T>>> table;
    size_t currentSize;

    size_t hashFunction(const K& key) const {
        return std::hash<K>{}(key) % table.size();
    }

public:
    HashTable(size_t capacity = 101) : table(capacity), currentSize(0) {}

    void insert(const K& key, const T& value) {
        size_t index = hashFunction(key);
        auto& bucket = table[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        ++currentSize;
    }

    void add(const K& key, T delta) {
        size_t idx = hashFunction(key);
        auto& bucket = table[idx];
        for (auto& kv : bucket) {
            if (kv.first == key) {
                kv.second += delta;   // acumula
                return;
            }
        }
        bucket.emplace_back(key, delta);
        ++currentSize;
    }

    bool find(const K& key, T& value) const {
        size_t index = hashFunction(key);
        const auto& bucket = table[index];
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        currentSize = 0;
    }

    size_t size() const {
        return currentSize;
    }

    // -------------------- ITERADOR PERSONALIZADO --------------------
    class iterator {
    private:
        using OuterIter = typename std::vector<std::vector<std::pair<K, T>>>::iterator;
        using InnerIter = typename std::vector<std::pair<K, T>>::iterator;

        OuterIter outer;
        OuterIter outerEnd;
        InnerIter inner;

        void avanzarHastaValido() {
            while (outer != outerEnd && inner == outer->end()) {
                ++outer;
                if (outer != outerEnd) inner = outer->begin();
            }
        }

    public:
        iterator(OuterIter out, OuterIter outEnd) : outer(out), outerEnd(outEnd) {
            if (outer != outerEnd)
                inner = outer->begin();
            avanzarHastaValido();
        }

        std::pair<K, T>& operator*() {
            return *inner;
        }

        std::pair<K, T>* operator->() {
            return &(*inner);
        }

        iterator& operator++() {
            ++inner;
            avanzarHastaValido();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return outer != other.outer || (outer != outerEnd && inner != other.inner);
        }
    };

    iterator begin() {
        return iterator(table.begin(), table.end());
    }

    iterator end() {
        return iterator(table.end(), table.end());
    }
};

