#ifndef ALGORITHM_SEARCHING_3_RED_BLACK_BST_H
#define ALGORITHM_SEARCHING_3_RED_BLACK_BST_H

#include "comparable.h"
#include <optional>
#include <iostream>
#include <cassert>
#include <queue>

template<Comparable KEY, typename VALUE>
class RedBlackBST {
private:
    struct Node {
        KEY key;
        VALUE value;
        Node *left;
        Node *right;
        bool is_red;

        Node(KEY k, VALUE v, bool red = true)
            : key(k), value(v), left(nullptr), right(nullptr), is_red(red) {}
    };

    Node *root_ = nullptr;

    bool is_red(Node *node) const {
        if (node == nullptr) return false;
        return node->is_red;
    }

    Node* rotateLeft(Node *h) {
        assert(h != nullptr && is_red(h->right));
        Node* x = h->right;
        h->right = x->left;
        x->left = h;
        x->is_red = h->is_red;
        h->is_red = true;
        return x;
    }

    Node* rotateRight(Node *h) {
        assert(h != nullptr && is_red(h->left));
        Node* x = h->left;
        h->left = x->right;
        x->right = h;
        x->is_red = h->is_red;
        h->is_red = true;
        return x;
    }

    void flipColor(Node *h) {
        assert(h != nullptr && h->left != nullptr && h->right != nullptr);
        assert(!is_red(h) && is_red(h->left) && is_red(h->right));
        h->is_red = true;
        h->left->is_red = false;
        h->right->is_red = false;
    }

    Node* put(Node *h, KEY key, VALUE value) {
        if (h == nullptr)
            return new Node(key, value, true);

        if (key < h->key)
            h->left = put(h->left, key, value);
        else if (key > h->key)
            h->right = put(h->right, key, value);
        else
            h->value = value;

        if (is_red(h->right) && !is_red(h->left)) h = rotateLeft(h);
        if (is_red(h->left) && is_red(h->left->left)) h = rotateRight(h);
        if (is_red(h->left) && is_red(h->right)) flipColor(h);

        return h;
    }

    const Node* get(Node *h, const KEY& key) const {
        while (h != nullptr) {
            if (key < h->key)
                h = h->left;
            else if (key > h->key)
                h = h->right;
            else
                return h;
        }
        return nullptr;
    }

public:
    bool is_empty() const {
        return root_ == nullptr;
    }

    void put(KEY key, VALUE value) {
        root_ = put(root_, key, value);
        root_->is_red = false;
    }

    std::optional<VALUE> get(const KEY& key) const {
        const Node* res = get(root_, key);
        if (res == nullptr) return std::nullopt;
        return res->value;
    }

    void print() const {
        std::cout << "Red-Black BST" << std::endl;
        std::queue<Node*> q;
        q.push(root_);
        while (!q.empty()) {
            int level_size = q.size();
            for (int i = 0; i < level_size; ++i) {
                Node* node = q.front();
                q.pop();
                std::cout << (node->is_red ? "R" : "B") << node->key << " ";
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            std::cout << std::endl;
        }
    }
};

void red_black_bst_test() {
    RedBlackBST<int, std::string> table;
    table.put(7, "date");
    table.put(5, "cherry");
    table.put(3, "banana");
    table.put(1, "apple");
    table.print();
}

#endif //ALGORITHM_SEARCHING_3_RED_BLACK_BST_H
