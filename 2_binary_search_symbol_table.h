#ifndef ALGORITHM_SEARCHING_2_BINARY_SEARCH_SYMBOL_TABLE_H
#define ALGORITHM_SEARCHING_2_BINARY_SEARCH_SYMBOL_TABLE_H

#include "comparable.h"
#include <optional>
#include <iostream>
#include <vector>

template<Comparable KEY, typename VALUE>
class BinarySearchSymbolTable {
public:
    void put(KEY key, const VALUE& value) {
        int i = rank(key);
        if (i < keys_.size() && keys_[i] == key) {
            values_[i] = value;
            return;
        }
        keys_.insert(keys_.begin() + i, key);
        values_.insert(values_.begin() + i, value);
    }

    std::optional<VALUE> get(KEY key) {
        if (is_empty()) return std::nullopt;
        int i = rank(key);
        if (i < keys_.size() && keys_[i] == key) {
            return values_[i];
        }
        return std::nullopt;
    }

    void remove(KEY key) {
        if (is_empty()) return;
        int i = rank(key);
        if (i < keys_.size() && keys_[i] == key) {
            keys_.erase(keys_.begin() + i);
            values_.erase(values_.begin() + i);
        }
    }

    // returns the number of keys in this symbol table strictly less than key.
    int rank(KEY key) {
        int left = 0, right = keys_.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2; // prevent integer overflow
            if (key < keys_[mid]) {
                right = mid - 1;
            } else if (key > keys_[mid]) {
                left = mid + 1;
            } else {
                return mid;
            }
        }
        return left;
    }

    std::optional<KEY> min() {
        if (is_empty()) return std::nullopt;
        return keys_.front();
    }

    std::optional<KEY> max() {
        if (is_empty()) return std::nullopt;
        return keys_.back();
    }

    std::optional<KEY> select(int k) {
        if (k < 0 || k >= keys_.size()) return std::nullopt;
        return keys_[k];
    }

    std::optional<KEY> ceiling(KEY key) { return select(rank(key)); }

    std::optional<KEY> floor(KEY key) { return select(rank(key) - 1); }

    bool contains(KEY key) { return get(key).has_value(); }

    bool is_empty() { return keys_.empty(); }

    size_t size() { return keys_.size(); }

    void print() {
        std::cout << "[" << size() << "] ";
        for (size_t i = 0; i < keys_.size(); i++) {
            std::cout << keys_[i] << " " << values_[i] << (i < keys_.size() - 1 ? " - " : "\n");
        }
    }

private:
    std::vector<KEY> keys_;
    std::vector<VALUE> values_;
};

void binary_search_symbol_table_test() {
    BinarySearchSymbolTable<int, std::string> table;
    table.put(7, "date");
    table.put(5, "cherry");
    table.put(3, "banana");
    table.put(1, "apple");
    table.print();
    std::cout << "min: " << table.min().value_or(-1) << std::endl;
    std::cout << "max: " << table.max().value_or(-1) << std::endl;
    std::cout << "select(2): " << table.select(2).value_or(-1) << std::endl;
    std::cout << "ceiling(6): " << table.ceiling(6).value_or(-1) << std::endl;
    std::cout << "floor(6): " << table.floor(6).value_or(-1) << std::endl;
    std::cout << "contains(3): " << table.contains(3) << std::endl;
    std::cout << "contains(4): " << table.contains(4) << std::endl;
    table.remove(3);
    table.print();
}

#endif //ALGORITHM_SEARCHING_2_BINARY_SEARCH_SYMBOL_TABLE_H
