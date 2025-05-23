#ifndef ALGORITHM_SEARCHING_1_SEQUENTIAL_SEARCH_SYMBOL_TABLE_H
#define ALGORITHM_SEARCHING_1_SEQUENTIAL_SEARCH_SYMBOL_TABLE_H

#include "comparable.h"
#include <optional>
#include <iostream>

template<Comparable KEY, typename VALUE>
class SequentialSearchSymbolTable {
public:
    ~SequentialSearchSymbolTable() {
        while (head_ != nullptr) {
            Node *old = head_;
            head_ = head_->next;
            delete old;
        }
    }

    void put(KEY key, VALUE value) {
        for (Node *x = head_; x != nullptr; x = x->next) {
            if (x->key == key) {
                x->value = value;
                return;
            }
        }
        head_ = new Node(key, value, head_);
        size_++;
    }

    std::optional<VALUE> get(KEY key) {
        if (is_empty()) return std::nullopt;
        for (Node *x = head_; x != nullptr; x = x->next) {
            if (x->key == key) {
                return x->value;
            }
        }
        return std::nullopt;
    }

    void remove(KEY key) {
        Node *previous = nullptr;
        for (Node *x = head_; x != nullptr; previous = x, x = x->next) {
            if (x->key == key) {
                if (previous != nullptr) {
                    previous->next = x->next;
                } else {
                    head_ = x->next;
                }
                delete x;
                size_--;
                return;
            }
        }
    }

    bool contains(KEY key) { return get(key).has_value(); }

    bool is_empty() { return head_ == nullptr; }

    size_t size() { return size_; }

    void print() {
        std::cout << "[" << size() << "] ";
        for (Node *x = head_; x != nullptr; x = x->next) {
            std::cout << x->key << " " << x->value << (x->next != nullptr ? " -> " : "\n");
        }
    }

private:
    struct Node {
        KEY key;
        VALUE value;
        Node *next;

        Node(KEY key, VALUE value, Node *next) : key(key), value(value), next(next) {}
    };

    Node *head_ = nullptr;
    size_t size_ = 0;
};

void sequential_search_symbol_table_test() {
    SequentialSearchSymbolTable<std::string, int> table;
    table.put("apple", 1);
    table.put("banana", 2);
    table.put("cherry", 3);
    table.print();
    if (table.contains("banana")) {
        std::cout << "banana: " << *table.get("banana") << std::endl;
    }
    table.remove("banana");
    table.print();
}

#endif //ALGORITHM_SEARCHING_1_SEQUENTIAL_SEARCH_SYMBOL_TABLE_H
